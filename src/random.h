#ifndef RANDOM_H__VFnaOfXzkz
#define RANDOM_H__VFnaOfXzkz

#include <cstdlib>
#include <limits>

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>


namespace Raytracer
{


// Returns a random 32-bit integer.
// See https://en.wikipedia.org/wiki/Xorshift
static thread_local uint32_t xorshiftState = 4229866139U;
uint32_t xorshift32();

// Maximum value that xorshift32() can return.
constexpr uint32_t XORSHIFT_RAND_MAX = std::numeric_limits<uint32_t>::max();

// Returns a random float between 0 and 1.
float linearRand();
float linearRand(float min, float max);

// Returns a random vector3 inside a sphere.
glm::vec3 ballRand();


inline uint32_t xorshift32() {
    uint32_t r = xorshiftState;
    r ^= r << 13;
    r ^= r >> 17;
    r ^= r << 5;
    return xorshiftState = r;
}


inline float linearRand()
{
    return xorshift32() / static_cast<float>(XORSHIFT_RAND_MAX);
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