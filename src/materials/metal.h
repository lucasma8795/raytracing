#ifndef MAT_METAL_H__3Jr5kAGAMd
#define MAT_METAL_H__3Jr5kAGAMd

#include "../material.h"

#include <glm/glm.hpp>


namespace Raytracer
{


class Metal: public Material
{
public:
    // Create a solid material.
    explicit Metal(glm::vec3 albedo, float fuzz) noexcept;

    // Whether if there is a scatter ray.
    virtual bool scatter(
        const Ray& incident, const HitPayload& payload, glm::vec3& attenuation, Ray& scatter
    ) const override;

    // Always does not emit anything.
    virtual glm::vec3 emitted(const glm::vec3& normal) const override;


private:
    // Characteristic colour of the metal material.
    glm::vec3 m_albedo;

    // A control of how fuzzy the metal surface is.
    float m_fuzz;
};


} // namespace Raytracer


#endif