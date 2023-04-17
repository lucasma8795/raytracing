#ifndef MATERIAL_H__jW529HT2J8
#define MATERIAL_H__jW529HT2J8

#include "ray.h"
#include "types.h"

#include <glm/glm.hpp>


namespace Raytracer
{


// Base class for all materials.
class Material
{
public:
    virtual ~Material() = default;

    // Whether the material produces a scatter ray, and if so, provides the direction of scatter.
    virtual bool scatter(
        const Ray& incident, const HitPayload& payload, glm::vec3& attenuation, Ray& scatter
    ) const = 0;

    // Light emitted by the material.
    // If the material does not emit any light, returns glm::vec3{0.0f}.
    // Returned value can be larger than 1.0f to make the material bright enough.
    virtual glm::vec3 emitted(float u, float v, const glm::vec3& p) const = 0;
};


} // namespace Raytracer


#endif