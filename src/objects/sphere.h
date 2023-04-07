#ifndef OBJ_SPHERE_H__3tvdWd7Pna
#define OBJ_SPHERE_H__3tvdWd7Pna

#include "../object.h"

#include <glm/glm.hpp>


namespace Raytracer
{


class Sphere: public Object
{
public:
    bool hit(const Ray& ray, float t_min, float t_max) const override;

private:
    glm::vec3 m_centre; // Centre of the circle.

    float m_radius; // Radius of the circle.
};


} // namespace Raytracer


#endif