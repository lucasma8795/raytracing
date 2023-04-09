#include "scene.h"

#include "colours.h"
#include "object.h"
#include "types.h"

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
        // we reached depth limit, stop gathering light
        return Colours::BLACK;

    HitPayload payload, best;
    std::shared_ptr<Object> closest_obj = nullptr;

    for (auto object: m_objects)
    {
        if (object->hit(ray, 0.001, INF, payload) && payload.t < best.t)
        {
            best = payload; // copy best hit payload to current payload
            closest_obj = object; // set closest object
        }
    }

    if (closest_obj) // we have a collision
    {
        glm::vec3 attenuation; // factor to attenuate scattered ray by.
        Ray scatter; // scatter ray direction, if any.
        
        glm::vec3 emitted = best.material->emitted(best.normal);

        if (best.material->scatter(ray, best, attenuation, scatter))
        {
            // we have a scatter ray; recursively trace the colour of the ray
            return emitted + attenuation * raytrace(scatter, depth-1);
        }

        // we don't have a scatter ray
        return emitted;
    }

    // we don't have a collision
    // return colour of the sky by lerping between 2 colours
    // return Colours::ANTIQUE_WHITE;
    return glm::mix(Colours::LIGHT_SKY_BLUE, Colours::LIGHT_CYAN, (ray.dir().y + 1) / 2);
}


} // namespace Raytracer