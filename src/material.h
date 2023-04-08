#ifndef MATERIAL_H__jW529HT2J8
#define MATERIAL_H__jW529HT2J8

#include <glm/glm.hpp>


namespace Raytracer
{


// Base class for all materials.
class Material
{
public:
    // Whether the material will produce scatter ray(s), and if so, provides the direction(s) of scatter.
    virtual bool scatter() const = 0;
};


} // namespace Raytracer


#endif