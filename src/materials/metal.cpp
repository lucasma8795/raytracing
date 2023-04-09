#include "metal.h"

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>


namespace Raytracer
{


Metal::Metal(glm::vec3 albedo, float fuzz) noexcept
    : m_albedo{albedo}, m_fuzz{glm::clamp(fuzz, 0.0f, 1.0f)}
{}


bool Metal::scatter(
    const Ray& incident, const HitPayload& payload, glm::vec3& attenuation, Ray& scatter
) const {
    glm::vec3 reflectDir = glm::reflect(incident.dir(), payload.normal);

    if (m_fuzz)
        reflectDir += m_fuzz * glm::ballRand(1.0f);

    attenuation = m_albedo;
    scatter = Ray{payload.point, reflectDir};

    // are we scattering below the surface?
    return true;
    // return glm::dot(scatter.dir(), payload.normal) > 0;
}


glm::vec3 Metal::emitted(const glm::vec3& normal) const
{
    return glm::vec3{0.0f};
}


} // namespace Raytracer