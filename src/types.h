#ifndef TYPES_H__I4ko1GsICr
#define TYPES_H__I4ko1GsICr

#include <memory>

#include <glm/glm.hpp>


namespace Raytracer
{


class Material;


// Useful constants
constexpr float INF = std::numeric_limits<float>::max();


// Structure to contain collision information between a ray and an object.
struct HitPayload
{
    float t = INF; // for ray.at(t)
    float u, v;    // Relative coordinates (between 0 and 1) on the surface.
    glm::vec3 p;   // Point of collision.
    glm::vec3 N;   // Normal vector of surface.
    std::shared_ptr<Material> material;
};


}


#endif