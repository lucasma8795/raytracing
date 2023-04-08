#ifndef SOLID_H__BSjpudQs3F
#define SOLID_H__BSjpudQs3F

#include "../material.h"

#include <glm/glm.hpp>


namespace Raytracer
{


class Solid: public Material
{
public:
    // Create a solid material.
    explicit Solid(glm::vec3 albedo) noexcept;

    // Always does not scatter.
    virtual bool scatter() const override;


private:
    // Characteristic colour of the solid material.
    glm::vec3 m_albedo;
};


} // namespace Raytracer


#endif