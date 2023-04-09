#include "dielectric.h"

#include "../types.h"

#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>


namespace Raytracer
{


Dielectric::Dielectric(float refractiveIndex) noexcept
    : m_ir{glm::max(refractiveIndex, 1.0f)}
{}


bool Dielectric::scatter(
    const Ray& incident, const HitPayload& payload, glm::vec3& attenuation, Ray& scatter
) const {
    // glass does not absorb any light
    attenuation = glm::vec3{1.0f};

    // are we bending towards or against the normal?
    bool isFrontFace = glm::dot(incident.dir(), payload.normal) < 0;
    float eta = isFrontFace ? (1.0f / m_ir) : m_ir; // refraction ratio

    float cosTheta = glm::min(glm::dot(-incident.dir(), payload.normal), 1.0f);
    float sinTheta = glm::sqrt(1 - cosTheta * cosTheta);

    bool totalInternalReflection = sinTheta * eta > 1.0f;

    glm::vec3 direction;

    if (totalInternalReflection || reflectance(cosTheta, eta) > glm::linearRand(0.0f, 1.0f)) // total internal reflection; must reflect
    {
        direction = glm::reflect(incident.dir(), payload.normal);
    }
    else // can refract
    {
        direction = glm::refract(incident.dir(), payload.normal, eta);
    }

    // attenuation = m_albedo;
    scatter = Ray{payload.point, direction};

    // are we scattering below the surface?
    return true;
}


glm::vec3 Dielectric::emitted(const glm::vec3& normal) const
{
    return glm::vec3{0.0f};
}


float Dielectric::reflectance(float cosTheta, float eta)
{
    float r0 = (1.0f - eta) / (1.0f + eta);
    r0 *= r0;
    return r0 + (1.0f - r0) * powf(1.0f - cosTheta, 5);

}


} // namespace Raytracer