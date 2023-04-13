#ifndef TYPES_H__I4ko1GsICr
#define TYPES_H__I4ko1GsICr

#include <memory>

#include <glm/glm.hpp>


namespace Raytracer
{


class Material;


// Useful constants
constexpr float INF = std::numeric_limits<float>::max();
constexpr glm::vec3 DIR_FRONT = glm::vec3{0.0f, 0.0f, -1.0f},
                    DIR_BACK  = glm::vec3{0.0f, 0.0f, +1.0f};


// Structure to contain collision information between a ray and an object.
struct HitPayload
{
    float t = INF; // for ray.at(t)
    float u, v;    // Scaled surface coordinates.
    glm::vec3 p;   // Point of collision.
    glm::vec3 N;   // Normal vector of surface.
    std::shared_ptr<Material> material;
    bool isFrontFace;
};


}


#endif