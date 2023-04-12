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


Camera::Camera() noexcept
{
    m_origin = glm::vec3{0.0f, 0.0f, 0.0f};
    // m_forwardDirection = glm::vec3{0.0f, 0.0f, 1.0f};
    // m_rightDirection   = glm::cross(m_forwardDirection, UP_DIRECTION);

    // Allocate memory for ray directions cache.
    m_rayDirs = std::make_unique_for_overwrite<glm::vec3[]>(NUM_PIXELS);

    // Compute cached ray directions.
    computeRayDirs();

    EventMgr.subscribe(Event::CAMERA_MOVE, std::bind(&Camera::dummy, this));
}


void Camera::dummy() const
{
    std::cout << "keypress!" << std::endl;
}


Ray Camera::getRay(int x, int y) const
{
    glm::vec3 random{
        linearRand() / WINDOW_WIDTH,
        linearRand() / WINDOW_HEIGHT,
        0.0f
    };

    return Ray{m_origin, m_rayDirs[y * WINDOW_WIDTH + x] + random};
}


void Camera::computeRayDirs()
{
    for (int y = 0; y < WINDOW_HEIGHT; ++y)
    {
        for (int x = 0; x < WINDOW_WIDTH; ++x)
        {
            glm::vec3 dir;
            dir.x = -ASPECT_RATIO + ASPECT_RATIO * 2 * (x / static_cast<float>(WINDOW_WIDTH));
            dir.y = 1.0f - 2.0f * (y / static_cast<float>(WINDOW_HEIGHT));
            dir.z = 1.0f;
            
            m_rayDirs[y * WINDOW_WIDTH + x] = glm::normalize(dir);
        }
    }
}


} // namespace Raytracer