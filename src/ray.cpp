#include "ray.h"


namespace Raytracer
{


Ray::Ray(const glm::vec3& origin, const glm::vec3& dir) noexcept
    : m_orig{origin}, m_dir{dir}
{}


Ray::Ray() noexcept {}


} // namespace Raytracer