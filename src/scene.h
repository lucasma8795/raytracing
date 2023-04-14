#ifndef SCENE_H__liMFPBg3qM
#define SCENE_H__liMFPBg3qM

#include "colours.h"
#include "object.h"

#include <memory>
#include <vector>

#include <glm/glm.hpp>


namespace Raytracer
{


// An object pointer.
template<class T>
concept ObjectPtr = std::is_convertible_v<T, std::shared_ptr<Object>>;

// Contains all information of a scene to be rendered.
// Additionally, also contains all raytracing facilities.
class Scene
{
public:
    // Trace the colour of a ray.
    glm::vec3 raytrace(const Ray& ray) const;
    glm::vec3 raytrace(const Ray& ray, int depth) const;

    // Add objects to the scene.
    template<ObjectPtr T> void add(T object);
    template<ObjectPtr T, typename... Args> void add(T object, Args... objects);


private:
    static glm::vec3 lightSkyColour(const glm::vec3& dir); // Returns light sky colour.
    static glm::vec3 darkSkyColour(const glm::vec3& dir);  // Returns dark sky colour.


private:
    std::vector<std::shared_ptr<Object>> m_objects; // Vector of object pointers to render.

    static constexpr int MAX_DEPTH = 16; // Maximum number of times a ray can bounce.
};


template<ObjectPtr T>
inline void Scene::add(T object)
{
    m_objects.push_back(object);
}


template<ObjectPtr T, typename... Args>
inline void Scene::add(T object, Args... objects)
{
    m_objects.push_back(object);
    add(objects...);
}


} // namespace Raytracer


#endif