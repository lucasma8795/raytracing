#ifndef MATH_H__VFnaOfXzkz
#define MATH_H__VFnaOfXzkz

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

// Fast approximation for atan2f and acosf.
float atan2f(float y, float x);
float acos(float x);


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


inline float atan2f(float y, float x)
{
    // https://gist.github.com/volkansalma/2972237
    constexpr float ONEQTR_PI = M_PI / 4.0;
	constexpr float THRQTR_PI = 3.0 * M_PI / 4.0;
	float r, angle;
	float abs_y = fabs(y) + 1e-10f; // kludge to prevent 0/0 condition
	if (x < 0.0f)
	{
		r = (x + abs_y) / (abs_y - x);
		angle = THRQTR_PI;
	}
	else
	{
		r = (x - abs_y) / (x + abs_y);
		angle = ONEQTR_PI;
	}
	angle += (0.1963f * r * r - 0.9817f) * r;
	if (y < 0.0f)
		return -angle; // negate if in quad III or IV
	else
		return angle;
}


inline float acosf(float x) {
    float negate = float(x < 0);
    x = abs(x);
    float ret = -0.0187293f;
    ret = ret * x;
    ret = ret + 0.0742610f;
    ret = ret * x;
    ret = ret - 0.2121144f;
    ret = ret * x;
    ret = ret + 1.5707288f;
    ret = ret * sqrt(1.0-x);
    ret = ret - 2 * negate * ret;
    return negate * M_PI + ret;
}


} // namespace Raytracer


#endif