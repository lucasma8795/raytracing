#ifndef MAT_LAMBERTIAN_H__GP5tzYrB47
#define MAT_LAMBERTIAN_H__GP5tzYrB47

#include "../material.h"
#include "../types.h"

#include <glm/glm.hpp>


namespace Raytracer
{


class Lambertian: public Material
{
public:
    // Create a lambertian material.
    explicit Lambertian(glm::vec3 albedo) noexcept;

    // Whether there is a scatter ray.
    virtual bool scatter(
        const Ray& incident, const HitPayload& payload, glm::vec3& attenuation, Ray& scatter
    ) const override;

    // Always does not emit any light.
    virtual glm::vec3 emitted(const glm::vec3& normal) const override;


private:
    // Characteristic colour of the solid material.
    glm::vec3 m_albedo;

};


} // namespace Raytracer


#endif