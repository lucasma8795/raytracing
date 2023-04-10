#ifndef SOLID_COLOUR_H__AbX20UPZ8p
#define SOLID_COLOUR_H__AbX20UPZ8p

#include "../texture.h"

#include <glm/glm.hpp>


namespace Raytracer
{

// A basic texture with a solid colour.
class SolidColour: public Texture
{
public:
    // Create a solid colour texture.
    explicit SolidColour(glm::vec3 albedo) noexcept;

    // Returns the colour of the solid texture.
    virtual glm::vec3 colourAt(float u, float v, const glm::vec3& p) const override;


private:
    glm::vec3 m_albedo;
};


} // namespace Raytracer


#endif