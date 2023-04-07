#include "camera.h"

#include "config.h"
#include "ray.h"

#include <memory>

#include <glm/glm.hpp>


namespace Raytracer
{


Camera::Camera() noexcept
{
    m_origin = glm::vec3{0.0f, 0.0f, 0.0f};
    m_direction = glm::vec3{0.0f, 0.0f, 1.0f};
    // m_upDirection = glm::vec3{0.0f, 0.0f, 1.0f};
    // m_rightDirection = 
    m_FOV = 90.0f;

    m_rays = std::make_unique_for_overwrite<glm::vec3[]>(NUM_PIXELS);
}


void Camera::update(float dt)
{

}


Ray Camera::getRay(int x, int y)
{
    return Ray{m_origin, m_rays[y * WINDOW_WIDTH + x]};
}


} // namespace Raytracer