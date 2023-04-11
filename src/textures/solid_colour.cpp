#include "solid_colour.h"


namespace Raytracer
{


SolidColour::SolidColour(glm::vec3 albedo) noexcept
    : m_albedo{albedo}
{}


glm::vec3 SolidColour::colourAt(
    float u __attribute__((unused)),
    float v __attribute__((unused)),
    const glm::vec3& p __attribute__((unused))
) const {
    return m_albedo;
}


} // namespace Raytracer