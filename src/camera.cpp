#include "camera.h"

#include "config.h"
#include "events.h"
#include "random.h"
#include "ray.h"

#include <functional>
#include <iostream>
#include <memory>

#include <glm/glm.hpp>


namespace Raytracer
{


using namespace std::placeholders;


Camera::Camera() noexcept
{
    m_origin = glm::vec3{0.0f, 0.0f, 0.0f};
    // m_forwardDirection = glm::vec3{0.0f, 0.0f, 1.0f};
    // m_rightDirection   = glm::cross(m_forwardDirection, UP_DIRECTION);

    // Allocate memory for ray directions cache.
    m_rayDirs = std::make_unique_for_overwrite<glm::vec3[]>(NUM_PIXELS);

    // Compute cached ray directions.
    computeRayDirs();

    // Subscribe to camera move events.
    g_eventMgr.subscribe<Events::CameraTranslate>(std::bind(&Camera::translateCamera, this, _1));
}


Ray Camera::getRay(int x, int y) const
{
    glm::vec3 random{
        linearRand() / VIEWPORT_WIDTH,
        linearRand() / VIEWPORT_HEIGHT,
        0.0f
    };

    return Ray{m_origin, m_rayDirs[y * VIEWPORT_WIDTH + x] + random};
}


void Camera::translateCamera(const Events::CameraTranslate& event)
{
    m_origin += event.dir * event.dt * CAMERA_MOVESPEED;
}


void Camera::computeRayDirs()
{
    for (int y = 0; y < VIEWPORT_HEIGHT; ++y)
    {
        for (int x = 0; x < VIEWPORT_WIDTH; ++x)
        {
            glm::vec3 dir{
                -ASPECT_RATIO + ASPECT_RATIO * 2 * (x / static_cast<float>(VIEWPORT_WIDTH)),
                1.0f - 2.0f * (y / static_cast<float>(VIEWPORT_HEIGHT)),
                m_focalLength
            };
            
            m_rayDirs[y * VIEWPORT_WIDTH + x] = glm::normalize(dir);
        }
    }
}


} // namespace Raytracer