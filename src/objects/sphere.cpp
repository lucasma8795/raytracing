#include "sphere.h"

#include <memory>


namespace Raytracer
{


Sphere::Sphere(glm::vec3 centre, float radius, std::shared_ptr<Material> material) noexcept
    : m_centre{centre}, m_radius{radius}
{
    m_material = material;
}


bool Sphere::hit(const Ray& ray, float t_min, float t_max) const
{
    return true;
}


} // namespace Raytracer