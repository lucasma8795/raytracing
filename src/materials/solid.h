#ifndef SOLID_H__BSjpudQs3F
#define SOLID_H__BSjpudQs3F

#include "../material.h"


namespace Raytracer
{


class Solid: public Material
{
public:
    // Always absorbs all light rays and does not scatter.
    virtual bool scatter() const override;


private:



};


} // namespace Raytracer


#endif