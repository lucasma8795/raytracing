#include "camera.h"

#include "event.h"
#include "ray.h"

#include <functional>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


namespace Raytracer
{


using namespace std::placeholders;


Camera::Camera() noexcept {}


Camera::Camera(size_t width, size_t height) noexcept
    : m_width{width}, m_height{height}
{
    // allocate memory for ray directions cache
    m_rayDirs.resize(width * height);

    // bind event listeners
    g_eventMgr.subscribe<Events::CameraTranslate>(std::bind(&Camera::onCameraTranslate, this, _1));
    g_eventMgr.subscribe<Events::CameraRotate>(std::bind(&Camera::onCameraRotate, this, _1));
    g_eventMgr.subscribe<Events::Update>(std::bind(&Camera::onUpdate, this, _1));

    // precomputations
    computeView();
    computeProjection();
    computeRayDirs();

    m_origin = glm::vec3{0.0f, 0.0f, 0.0f};
}


Ray Camera::getRay(size_t x, size_t y) const
{
    return Ray(m_origin, m_rayDirs.at(y * m_width + x));
}


void Camera::computeRayDirs()
{
    for (size_t y = 0; y < m_height; ++y)
    {
        for (size_t x = 0; x < m_width; ++x)
        {
            glm::vec2 coord{x / static_cast<float>(m_width), y / static_cast<float>(m_height)};
            coord = 1.0f - coord * 2.0f; // -1 -> 1

            glm::vec4 target = m_inverseProjection * glm::vec4(coord.x, coord.y, 1.0f, 1.0f);
            glm::vec3 rayDir = glm::vec3(m_inverseView * glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0.0f));
            
            m_rayDirs[y * m_width + x] = rayDir;
        }
    }
}


void Camera::computeProjection()
{
    m_projection = glm::perspectiveFov(
        glm::radians(VERTICAL_FOV),
        static_cast<float>(m_width),
        static_cast<float>(m_height),
        NEAR_CLIP,
        FAR_CLIP
    );
    m_inverseProjection = glm::inverse(m_projection);
}


void Camera::computeView()
{
    m_view = glm::lookAt(m_origin, m_origin + m_forwardDirection, glm::vec3{0.0f, 1.0f, 0.0f});
    m_inverseView = glm::inverse(m_view);
}


void Camera::onCameraTranslate(const Events::CameraTranslate& event)
{
    m_origin += event.direction * event.dt * MOVE_SPEED;

    m_moved = true;
}


void Camera::onCameraRotate(const Events::CameraRotate& event)
{
    float pitchDelta = event.rotation.y * ROTATION_SPEED;
    float yawDelta = event.rotation.x * ROTATION_SPEED;

    glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, m_rightDirection),
    	    glm::angleAxis(-yawDelta, glm::vec3(0.0f, 1.0f, 0.0f))));
    
    m_forwardDirection = glm::rotate(q, m_forwardDirection);
    m_rightDirection = glm::cross(m_forwardDirection, m_upDirection);

    m_moved = true;
}


void Camera::onUpdate(const Events::Update& event)
{
    if (!m_moved) return;

    computeView();
    computeProjection();
    computeRayDirs();

    m_moved = false;
}


void Camera::onWindowResize(const Events::WindowResize& event)
{
    m_width = event.width;
    m_height = event.height;
    m_rayDirs.resize(m_width * m_height);

    m_moved = true;
}


} // namespace Raytracer