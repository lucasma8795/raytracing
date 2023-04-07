#ifndef SCENE_H__liMFPBg3qM
#define SCENE_H__liMFPBg3qM

#include "object.h"

#include <memory>
#include <vector>

#include <glm/glm.hpp>


namespace Raytracer
{


class Scene
{
public:
    // Trace the colour of a ray.
    glm::vec3 raytrace(const Ray& ray);

    // Add objects to the scene.
    void add(std::shared_ptr<Object> object);
    template<typename... Args> void add(std::shared_ptr<Object> object, Args... args);

private:
    std::vector<std::shared_ptr<Object>> m_objects;
};


} // namespace Raytracer


#endif