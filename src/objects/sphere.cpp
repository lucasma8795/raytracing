#include "sphere.h"

#include "../types.h"

#include <memory>

#include <glm/gtx/norm.hpp>


namespace Raytracer
{


Sphere::Sphere(glm::vec3 centre, float radius, std::shared_ptr<Material> material) noexcept
    : m_centre{centre}, m_radius{radius}
{
    m_material = material;
}


bool Sphere::hit(const Ray& ray, float t_min, float t_max, HitPayload& payload) const
{
    glm::vec3 oc = ray.origin() - m_centre;

    // modified quadratic equation to check if there is an intersection
    float a            = glm::length2(ray.dir());
    float half_b       = glm::dot(oc, ray.dir());
    float c            = glm::length2(oc) - m_radius * m_radius;
    float discriminant = half_b * half_b - a * c;

    if (discriminant < 0) return false; // no real roots -> no intersection

    // update collision payload information
    payload.t = (-half_b - glm::sqrt(discriminant)) / a;

    if (payload.t < t_min || payload.t > t_max)
        return false; // outside of requested t range

    payload.point = ray.at(payload.t);
    payload.material = m_material;
    payload.normal = (payload.point - m_centre) / m_radius;

    // glm::vec3 outwardNormal = (payload.point - m_centre) / m_radius;
    // bool frontFace = glm::dot(ray.dir(), outwardNormal);
    // payload.normal = frontFace ? outwardNormal : -outwardNormal;

    return true;
}


} // namespace Raytracer