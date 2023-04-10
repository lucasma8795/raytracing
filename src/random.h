#ifndef RANDOM_H__VFnaOfXzkz
#define RANDOM_H__VFnaOfXzkz

#include <stdio.h>
#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>


namespace Raytracer
{

// Returns a random float between 0 and 1.
float linearRand();
float linearRand(float min, float max);

// Returns a random vector3 inside a sphere.
glm::vec3 ballRand();


inline float linearRand()
{
    return rand() / static_cast<float>(RAND_MAX);
}


inline float linearRand(float min, float max)
{
    return min + linearRand() * (max - min);
}


inline glm::vec3 ballRand()
{
    glm::vec3 r;
    do
    {
        r = glm::vec3{linearRand(-1.0f, 1.0f), linearRand(-1.0f, 1.0f), linearRand(-1.0f, 1.0f)};
    } while (glm::length2(r) > 1.0f);
    return r;
}


} // namespace Raytracer


#endif