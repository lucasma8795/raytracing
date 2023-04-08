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
        // we reached depth limit, assume the ray colour is insignificant anyway
        return Colours::BLACK;

    HitPayload payload;
    float t_min = std::numeric_limits<float>::max(); // minimum ray distance so far

    for (auto object: m_objects)
    {
        if (object->hit(ray, 0.001, std::numeric_limits<float>::max(), payload))
        {
            return (payload.N * glm::vec3{1.0f, -1.0f, -1.0f} + 1.0f) * 0.5f;
        }
    }

    // return colour of the sky by lerping between 2 colours
    return glm::mix(Colours::LIGHT_SKY_BLUE, Colours::LIGHT_CYAN, (ray.dir().y + 1) / 2);
}


} // namespace Raytracer