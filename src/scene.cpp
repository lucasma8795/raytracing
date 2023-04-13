#include "scene.h"

#include "colours.h"
#include "object.h"
#include "types.h"

#include <glm/glm.hpp>


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
    bool hit = false;

    for (auto object: m_objects)
    {
        if (object->hit(ray, 0.001, INF, payload) && payload.t < best.t)
        {
            hit = true;
            best = payload; // copy best hit payload to current payload
        }
    }

    if (hit) // we have a collision
    {
        glm::vec3 attenuation; // factor to attenuate scattered ray by.
        Ray scatter; // scatter ray direction, if any.
        
        glm::vec3 emitted = best.material->emitted(best.u, best.v, best.p);

        if (best.material->scatter(ray, best, attenuation, scatter))
        {
            // we have a scatter ray; recursively trace the colour of the ray
            return emitted + attenuation * raytrace(scatter, depth-1);
        }

        // we don't have a scatter ray
        return emitted;
    }

    // we don't have a collision
    // return skyColour(ray.dir());
    // return Colours::BLACK;
    return lightSkyColour(ray.dir());
}


glm::vec3 Scene::lightSkyColour(const glm::vec3& dir)
{
    // we assume input is normalized
    return glm::mix(Colours::WHITE, glm::vec3{0.5f, 0.7f, 1.0f}, (dir.y + 1) / 2);
}


glm::vec3 Scene::darkSkyColour(const glm::vec3& dir)
{
    // we assume input is normalized
    return glm::mix(Colours::BLACK, glm::vec3{0.043f, 0.063f, 0.148f} * 3.0f, (dir.y + 1) / 2);
}


} // namespace Raytracer