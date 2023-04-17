#ifndef CAMERA_H_NEW__V0BzYl9Qt8
#define CAMERA_H_NEW__V0BzYl9Qt8

#include "events.h"
#include "ray.h"

#include <vector>

#include <glm/glm.hpp>


namespace Raytracer
{


class Camera
{
public:
    // Create a camera object.
    Camera() noexcept;
    explicit Camera(size_t width, size_t height) noexcept;

    // Get the ray pointing from camera origin to given screen coordinates.
    Ray getRay(size_t x, size_t y) const;


private:
    // Precomputation.
    void computeRayDirs();
    void computeProjection();
    void computeView();

    // Event handlers.
    void onCameraTranslate(const Events::CameraTranslate& event);
    void onCameraRotate(const Events::CameraRotate& event);
    void onWindowResize(const Events::WindowResize& event);
    void onUpdate(const Events::Update& event);


private:
    static constexpr float MOVE_SPEED     = 4.0f; // units/sec
    static constexpr float ROTATION_SPEED = 0.5f; // rad/sec

    static constexpr float NEAR_CLIP = 1.0f;
    static constexpr float FAR_CLIP  = 100.0f;

    static constexpr float VERTICAL_FOV = 45.0f;

    size_t m_width = 0U;  // Viewport width.
    size_t m_height = 0U; // Viewport height.

    glm::vec3 m_origin{0.0f}; // Camera position.

    glm::vec3 m_forwardDirection{0.0f, 0.0f, 1.0f};
    static constexpr glm::vec3 m_upDirection{0.0f, 1.0f, 0.0f};
    glm::vec3 m_rightDirection{1.0f, 0.0f, 0.0f};

    // Projection matrixes.
    glm::mat4 m_projection{1.0f};
    glm::mat4 m_inverseProjection{1.0f};
    glm::mat4 m_view{1.0f};
    glm::mat4 m_inverseView{1.0f};

    bool m_moved = false; // Whether a camera has moved and needs updating.

public:
    std::vector<glm::vec3> m_rayDirs; // Cached ray directions.
};


} // namespace Raytracer


#endif