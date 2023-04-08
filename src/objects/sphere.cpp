#include "sphere.h"

#include <iostream>
#include <memory>

#include <glm/gtx/norm.hpp>


namespace Raytracer
{


Sphere::Sphere(glm::vec3 centre, float radius, std::shared_ptr<Material> material) noexcept
    : m_centre{centre}, m_radius{radius}
{
    m_material = material;
}


bool Sphere::hit(const Ray& ray, float t_min, float t_max) const
{
    glm::vec3 oc = ray.origin() - m_centre;

    // Modified quadratic equation to check if there is an intersection.
    float a            = glm::length2(ray.dir());
    float half_b       = glm::dot(oc, ray.dir());
    float c            = glm::length2(oc) - m_radius * m_radius;
    float discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
        return false; // no real roots -> no intersection

    
    

    return true;
}


} // namespace Raytracer