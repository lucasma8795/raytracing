#ifndef CAMERA_H__V0BzYl9Qt8
#define CAMERA_H__V0BzYl9Qt8

#include "ray.h"

#include <memory>

#include <glm/glm.hpp>


namespace Raytracer
{


class Camera
{
public:
    // Create a new camera.
    explicit Camera() noexcept;

    // Delete copy constructor and assignment operator.
    Camera(const Camera&) = delete;
    Camera& operator=(Camera const&) = delete;

    // Update the camera.
    void update(float dt);

    // Get the ray pointing from camera origin to given screen coordinates.
    Ray getRay(int x, int y);


private:
    void computeRayDirs(); // Compute cached ray directions.


private:
    glm::vec3 m_origin; // Origin of the camera.

    // glm::vec3 m_forwardDirection; // Direction that the camera is pointing at.
    // glm::vec3 m_rightDirection;   // Right direction relative to camera position.

    // static constexpr glm::vec3 UP_DIRECTION{0.0f, 1.0f, 0.0f}; // Fixed up direction. (i.e.: no tilting)

    // static constexpr float m_verticalFOV = 45.0f; // Vertical field of view.

    // float m_nearClip; // Near clip plane.
    // float m_farClip;  // Far clip plane.

    std::unique_ptr<glm::vec3[]> m_rayDirs; // Cached ray directions for each pixel.
};


} // namespace Raytracer


#endif