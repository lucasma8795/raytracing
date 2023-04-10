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
    // glass does not absorb any light (i.e.: no attenuation)
    attenuation = glm::vec3{1.0f};

    // are we bending towards or against the normal?
    bool isFrontFace = glm::dot(incident.dir(), payload.N) < 0;

    float eta = isFrontFace ? (1.0f / m_ir) : m_ir; // refraction ratio

    float cosTheta = glm::min(glm::dot(-incident.dir(), payload.N), 1.0f);
    float sinTheta = glm::sqrt(1 - cosTheta * cosTheta);

    // is there total internal refraction?
    bool totalInternalReflection = (sinTheta * eta) > 1.0f;

    glm::vec3 direction; // reflection / refraction direction

    if (totalInternalReflection || reflectance(cosTheta, eta) > glm::linearRand(0.0f, 1.0f))
    {
        // must reflect
        direction = glm::normalize(glm::reflect(incident.dir(), payload.N));
    }
    else
    {
        // can refract
        direction = glm::normalize(glm::refract(incident.dir(), payload.N, eta));
    }

    scatter = Ray{payload.p, direction};

    return true; // always reflect/refract
}


glm::vec3 Dielectric::emitted(float u, float v, const glm::vec3& p) const
{
    return glm::vec3{0.0f}; // always do not emit any light
}


float Dielectric::reflectance(float cosTheta, float eta)
{
    // https://en.wikipedia.org/wiki/Schlick%27s_approximation
    float r0 = (1.0f - eta) / (1.0f + eta);
    r0 *= r0;
    return r0 + (1.0f - r0) * powf(1.0f - cosTheta, 5);
}


} // namespace Raytracer