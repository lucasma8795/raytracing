#include "camera.h"

#include "config.h"
#include "ray.h"

#include <memory>

#include <glm/glm.hpp>


namespace Raytracer
{


Camera::Camera() noexcept
{
    m_origin           = glm::vec3{0.0f, 0.0f, 0.0f};
    m_forwardDirection = glm::vec3{0.0f, 0.0f, 1.0f};
    m_rightDirection   = glm::cross(m_forwardDirection, UP_DIRECTION);

    // Allocate memory for ray directions cache.
    m_rayDirs = std::make_unique_for_overwrite<glm::vec3[]>(NUM_PIXELS);
}


void Camera::update(float dt)
{

}


Ray Camera::getRay(int x, int y)
{
    return Ray{m_origin, m_rayDirs[y * WINDOW_WIDTH + x]};
}


void Camera::computeRayDirs()
{

}


} // namespace Raytracer