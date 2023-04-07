#include "scene.h"

#include "object.h"

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>


namespace Raytracer
{


glm::vec3 Scene::raytrace(const Ray& ray)
{
    // return glm::ballRand(1.0f);
    return glm::vec3{0.0f, 0.410f, 0.578f};
}


void Scene::add(std::shared_ptr<Object> object)
{
    m_objects.push_back(object);
}


template<typename... Args>
void Scene::add(std::shared_ptr<Object> object, Args... args)
{
    // Recursively push_back() to object vector.
    m_objects.push_back(object);
    add(args...);
}


} // namespace Raytracer