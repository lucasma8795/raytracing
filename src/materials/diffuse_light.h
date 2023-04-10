#ifndef DIFFUSE_LIGHT_H__xSnDlJpmkZ
#define DIFFUSE_LIGHT_H__xSnDlJpmkZ

#include "../material.h"
#include "../texture.h"
#include "../types.h"

#include <memory>

#include <glm/glm.hpp>


namespace Raytracer
{


class DiffuseLight: public Material
{
public:
    // Create a diffuse light material.
    explicit DiffuseLight(glm::vec3 albedo) noexcept;
    explicit DiffuseLight(std::shared_ptr<Texture> texture) noexcept;

    // Always does not produce a scatter ray.
    virtual bool scatter(
        const Ray& incident, const HitPayload& payload, glm::vec3& attenuation, Ray& scatter
    ) const override;

    // Always emits light.
    virtual glm::vec3 emitted(float u, float v, const glm::vec3& p) const override;


private:
    // Texture to use for the material.
    std::shared_ptr<Texture> m_texture;
};


} // namespace Raytracer


#endif