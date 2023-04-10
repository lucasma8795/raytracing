#include "metal.h"

#include "../textures/solid_colour.h"
#include "../texture.h"
#include "../types.h"

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>


namespace Raytracer
{


Metal::Metal(glm::vec3 albedo, float fuzz) noexcept
    : m_texture{std::make_shared<SolidColour>(albedo)},
      m_fuzz{glm::clamp(fuzz, 0.0f, 1.0f)} // 0 <= fuzz <= 1
{}


Metal::Metal(std::shared_ptr<Texture> texture, float fuzz) noexcept
    : m_texture{texture},
      m_fuzz{glm::clamp(fuzz, 0.0f, 1.0f)} // 0 <= fuzz <= 1
{}


bool Metal::scatter(
    const Ray& incident, const HitPayload& payload, glm::vec3& attenuation, Ray& scatter
) const {
    // reflection direction
    glm::vec3 reflectDir = glm::reflect(incident.dir(), payload.N);

    // add fuzz to the metal surface
    if (m_fuzz)
        reflectDir += m_fuzz * glm::ballRand(1.0f);

    // update attenuation and scatter ray
    attenuation = m_texture->colourAt(payload.u, payload.v, payload.p);
    scatter = Ray{payload.p, reflectDir};

    // are we scattering below the surface?
    return glm::dot(scatter.dir(), payload.N) > 0;
}


glm::vec3 Metal::emitted(float u, float v, const glm::vec3& p) const
{
    return glm::vec3{0.0f}; // always do not emit any light
}


} // namespace Raytracer