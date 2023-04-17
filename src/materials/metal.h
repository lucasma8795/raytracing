#ifndef METAL_H__3Jr5kAGAMd
#define METAL_H__3Jr5kAGAMd

#include "../material.h"
#include "../texture.h"
#include "../types.h"

#include <memory>

#include <glm/glm.hpp>


namespace Raytracer
{


// A metallic surface that perfectly reflects light rays.
class Metal: public Material
{
public:
    // Create a solid material.
    explicit Metal(glm::vec3 albedo, float fuzz) noexcept;
    explicit Metal(std::shared_ptr<Texture> texture, float fuzz) noexcept;

    // Destructor.
    virtual ~Metal() = default;

    // Whether if there is a scatter ray.
    virtual bool scatter(
        const Ray& incident, const HitPayload& payload, glm::vec3& attenuation, Ray& scatter
    ) const override;

    // Always does not emit any light.
    virtual glm::vec3 emitted(float u, float v, const glm::vec3& p) const override;


private:
    // Texture to use for the material.
    std::shared_ptr<Texture> m_texture;

    // A control of how fuzzy the metal surface is.
    float m_fuzz;
};


} // namespace Raytracer


#endif