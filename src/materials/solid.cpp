#include "solid.h"

#include <glm/glm.hpp>


namespace Raytracer
{


Solid::Solid(glm::vec3 albedo) noexcept
    : m_albedo{albedo}
{}


bool Solid::scatter() const
{
    return false;
}


} // namespace Raytracer