#ifndef SCENE_H__liMFPBg3qM
#define SCENE_H__liMFPBg3qM

#include "object.h"

#include <memory>
#include <vector>

#include <glm/glm.hpp>


namespace Raytracer
{


// Contains all information of a scene to be rendered.
// Additionally, also contains all raytracing facilities.
class Scene
{
public:
    // Trace the colour of a ray.
    glm::vec3 raytrace(const Ray& ray) const;
    glm::vec3 raytrace(const Ray& ray, int depth) const;

    // Add objects to the scene.
    template<typename T> void add(T object);
    template<typename T, typename... Args> void add(T object, Args... objects);


private:
    std::vector<std::shared_ptr<Object>> m_objects; // Vector of object pointers to render.

    static constexpr int MAX_DEPTH = 1; // Maximum number of times a ray can bounce.

    // static constexpr int SAMPLES_PER_PIXEL = 1; // Number of samples to take per pixel.
    // static constexpr float SAMPLES_PER_PIXEL_INV = 1.0f / SAMPLES_PER_PIXEL;
};


template<typename T>
inline void Scene::add(T object)
{
    // Check if is shared_ptr to child classes of object.
    static_assert(
        std::is_convertible_v<T, std::shared_ptr<Object>>,
        "Argument not convertible to object pointer!"
    );

    m_objects.push_back(object);
}


template<typename T, typename... Args>
inline void Scene::add(T object, Args... objects)
{
    // Check if is shared_ptr to child classes of object.
    static_assert(
        std::is_convertible_v<T, std::shared_ptr<Object>>,
        "Argument not convertible to object pointer!"
    );

    // Recursively push_back() to object vector.
    m_objects.push_back(object);
    add(objects...);
}


} // namespace Raytracer


#endif