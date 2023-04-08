#ifndef OBJ_SPHERE_H__3tvdWd7Pna
#define OBJ_SPHERE_H__3tvdWd7Pna

#include "../material.h"
#include "../object.h"

#include <glm/glm.hpp>


namespace Raytracer
{


class Sphere: public Object
{
public:
    // Construct a new sphere.
    explicit Sphere(glm::vec3 centre, float radius, std::shared_ptr<Material> material) noexcept;

    // Whether the given ray intersects us.
    bool hit(const Ray& ray, float t_min, float t_max) const override;


private:
    glm::vec3 m_centre; // Centre of the circle.

    float m_radius; // Radius of the circle.
};


} // namespace Raytracer


#endif