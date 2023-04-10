#include "lambertian.h"

#include "../random.h"
#include "../textures/solid_colour.h"
#include "../texture.h"
#include "../types.h"

#include <algorithm>

#include <glm/glm.hpp>


namespace Raytracer
{


Lambertian::Lambertian(glm::vec3 albedo) noexcept
    : m_texture{std::make_shared<SolidColour>(albedo)}
{}


Lambertian::Lambertian(std::shared_ptr<Texture> texture) noexcept
    : m_texture{texture}
{}


bool Lambertian::scatter(
    const Ray& incident, const HitPayload& payload, glm::vec3& attenuation, Ray& scatter
) const {
    // perfectly diffuse scatter direction
    glm::vec3 scatterDirection = glm::normalize(payload.N + ballRand());

    // update attenuation and scatter ray
    attenuation = m_texture->colourAt(payload.u, payload.v, payload.p);
    scatter = Ray{payload.p, scatterDirection};

    return true; // always scatter
}


glm::vec3 Lambertian::emitted(float u, float v, const glm::vec3& p) const
{
    return glm::vec3{0.0f}; // always do not emit any light
}


} // namespace Raytracer