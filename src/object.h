#ifndef OBJECT_H__mFL5QuXZVE
#define OBJECT_H__mFL5QuXZVE

#include "material.h"
#include "ray.h"

#include <memory>


namespace Raytracer
{


// Base class for all objects.
class Object
{
public:
    // Whether the given ray intersects us.
    virtual bool hit(const Ray& ray, float tMin, float tMax) const = 0;


protected:
    // Material to use for the object.
    std::shared_ptr<Material> m_material;
};


} // namespace Raytracer


#endif