#ifndef TYPES_H__I4ko1GsICr
#define TYPES_H__I4ko1GsICr

#include <memory>

#include <glm/glm.hpp>


namespace Raytracer
{


class Material;


// Useful constants
constexpr float INF = std::numeric_limits<float>::max();
constexpr glm::vec3 DIR_FRONT = glm::vec3{+0.0f, +0.0f, +1.0f},
                    DIR_BACK  = glm::vec3{+0.0f, +0.0f, -1.0f},
                    DIR_LEFT  = glm::vec3{-1.0f, +0.0f, +0.0f},
                    DIR_RIGHT = glm::vec3{+1.0f, +0.0f, +0.0f},
                    DIR_UP    = glm::vec3{+0.0f, +1.0f, +0.0f},
                    DIR_DOWN  = glm::vec3{+0.0f, -1.0f, +0.0f};


// Structure to contain collision information between a ray and an object.
struct HitPayload
{
    float t = INF; // Units from ray origin in the direction of the ray.
    float u, v;    // Scaled surface coordinates.
    glm::vec3 p;   // Point of collision.
    glm::vec3 N;   // Normal vector of surface.
    std::shared_ptr<Material> material; // Material of collided surface.
    bool isFrontFace;
};


}


#endif