#ifndef TEXTURE_H__rDLdMJtBcG
#define TEXTURE_H__rDLdMJtBcG

#include <glm/glm.hpp>


namespace Raytracer
{


// Base class for all textures.
class Texture
{
public:
    virtual ~Texture() = default;

    // Gets the colour of the texture at coordinates (u, v).
    virtual glm::vec3 colourAt(float u, float v, const glm::vec3& p) const = 0;
};


} // namespace Raytracer


#endif
