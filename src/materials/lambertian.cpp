#include "lambertian.h"

#include "../types.h"

#include <glm/gtc/random.hpp>


namespace Raytracer
{


Lambertian::Lambertian(glm::vec3 albedo) noexcept
    : m_albedo{albedo}
{}


bool Lambertian::scatter(
    const Ray& incident, const HitPayload& payload, glm::vec3& attenuation, Ray& scatter
) const {
    attenuation = m_albedo;

    // glm::vec3 randomInHemisphere = glm::ballRand(1.0f);
    // if (glm::dot(payload.normal, randomInHemisphere) < 0.0f)
    //     randomInHemisphere = -randomInHemisphere;
    glm::vec3 scatterDir = payload.normal + glm::ballRand(1.0f);

    scatter = Ray{payload.point, scatterDir};

    return true;
}


glm::vec3 Lambertian::emitted(const glm::vec3& normal) const
{
    return glm::vec3{0.0f};
}


} // namespace Raytracer