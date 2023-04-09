#ifndef MAT_DIELECTRIC_H__9ZFgdumO18
#define MAT_DIELECTRIC_H__9ZFgdumO18

#include "../material.h"
#include "../types.h"

#include <glm/glm.hpp>


namespace Raytracer
{


// A "clear" surface that splits light rays into reflected and refracted rays.
class Dielectric: public Material
{
public:
    // Create a glass material.
    explicit Dielectric(float refractiveIndex) noexcept;

    // Split into either a reflect or a refract ray.
    virtual bool scatter(
        const Ray& incident, const HitPayload& payload, glm::vec3& attenuation, Ray& scatter
    ) const override;

    // Always does not emit any light.
    virtual glm::vec3 emitted(const glm::vec3& normal) const override;


private:
    float m_ir; // Index of refraction.


private:
    // Schlick's approximation for reflectance.
    static float reflectance(float cosTheta, float eta);

};


} // namespace Raytracer


#endif