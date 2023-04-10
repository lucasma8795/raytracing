#ifndef LAMBERTIAN_H__GP5tzYrB47
#define LAMBERTIAN_H__GP5tzYrB47

#include "../material.h"
#include "../texture.h"
#include "../types.h"

#include <memory>

#include <glm/glm.hpp>


namespace Raytracer
{


// An ideal "matte" or perfectly diffuse material.
class Lambertian: public Material
{
public:
    // Create a lambertian material.
    explicit Lambertian(glm::vec3 albedo) noexcept;
    explicit Lambertian(std::shared_ptr<Texture> texture) noexcept;

    // Whether there is a scatter ray.
    virtual bool scatter(
        const Ray& incident, const HitPayload& payload, glm::vec3& attenuation, Ray& scatter
    ) const override;

    // Always does not emit any light.
    virtual glm::vec3 emitted(float u, float v, const glm::vec3& p) const override;


private:
    // Texture to use for the material.
    std::shared_ptr<Texture> m_texture;
};


} // namespace Raytracer


#endif