#ifndef MAT_SURFACE_NORMAL_H__OR87Xo6Uhh
#define MAT_SURFACE_NORMAL_H__OR87Xo6Uhh

#include "../material.h"
#include "../types.h"

#include <glm/glm.hpp>



namespace Raytracer
{


// A surface with colouring based on its surface normal.
class SurfaceNormal: public Material
{
public:
    // Create a surface normal coloured material.
    SurfaceNormal() noexcept;

    // Always does not scatter.
    virtual bool scatter(
        const Ray& incident, const HitPayload& payload, glm::vec3& attenuation, Ray& scatter
    ) const override;

    // Always emits a colour calculated from the surface normal.
    virtual glm::vec3 emitted(const glm::vec3& normal) const override;

};


} // namespace Raytracer


#endif