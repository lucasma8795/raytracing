#include "diffuse_light.h"

#include "../textures/solid_colour.h"
#include "../texture.h"
#include "../types.h"

#include <memory>

#include <glm/glm.hpp>


namespace Raytracer
{


DiffuseLight::DiffuseLight(glm::vec3 albedo) noexcept
    : m_texture{std::make_shared<SolidColour>(albedo)}
{}


DiffuseLight::DiffuseLight(std::shared_ptr<Texture> texture) noexcept
    : m_texture{texture}
{}


bool DiffuseLight::scatter(
    const Ray& incident, const HitPayload& payload, glm::vec3& attenuation, Ray& scatter
) const {
    return false; // always do not scatter
}


glm::vec3 DiffuseLight::emitted(float u, float v, const glm::vec3& p) const
{
    return m_texture->colourAt(u, v, p); // always emit light
}


} // namespace Raytracer