#include "scene.h"

#include "colours.h"
#include "object.h"

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>


namespace Raytracer
{


glm::vec3 Scene::raytrace(const Ray& ray) const
{
    return raytrace(ray, MAX_DEPTH);
}


glm::vec3 Scene::raytrace(const Ray& ray, int depth) const
{
    if (depth == 0)
        return Colours::BLACK;

    for (auto object: m_objects)
    {
        if (object->hit(ray, 0.001, std::numeric_limits<float>::max()))
        {
            return Colours::RED;
        }
    }

    // return colour of the sky
    return Colours::SKY_BLUE;
}


} // namespace Raytracer