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
    // glm::vec3 color{0.0f};
    // for (int i = 0; i < SAMPLES_PER_PIXEL; ++i)
    // {
    //     color += raytrace(ray, MAX_DEPTH);
    // }
    // return color * (1.0f / SAMPLES_PER_PIXEL);
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
    // return colour of the sky by lerping between 2 colours
    // return skyColour(ray.dir());
    // return Colours::BLACK;
    return lightSkyColour(ray.dir());
}


glm::vec3 Scene::lightSkyColour(const glm::vec3& dir) const
{
    // we assume input is normalized
    return glm::mix(Colours::LIGHT_SKY_BLUE, Colours::LIGHT_CYAN, (dir.y + 1) / 2);
}


glm::vec3 Scene::darkSkyColour(const glm::vec3& dir) const
{
    return glm::mix(Colours::BLACK, glm::vec3{0.04296875f, 0.0625f, 0.1484375f}, (dir.y + 1) / 2);
}


} // namespace Raytracer