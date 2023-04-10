#include "solid_colour.h"


namespace Raytracer
{


SolidColour::SolidColour(glm::vec3 albedo) noexcept
    : m_albedo{albedo}
{}


glm::vec3 SolidColour::colourAt(float u, float v, const glm::vec3& p) const
{
    return m_albedo;
}


} // namespace Raytracer