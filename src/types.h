#ifndef TYPES_H__I4ko1GsICr
#define TYPES_H__I4ko1GsICr

#include <glm/glm.hpp>


namespace Raytracer
{



struct HitPayload
{
    float t; // for ray.at(t)
    glm::vec3 P; // Point of collision.
    glm::vec3 N; // Normal vector of surface.
};


}


#endif