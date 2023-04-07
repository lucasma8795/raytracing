#ifndef OBJECT_H__mFL5QuXZVE
#define OBJECT_H__mFL5QuXZVE

#include "material.h"
#include "ray.h"

#include <memory>

#include <glm/glm.hpp>


namespace Raytracer
{


// Base class for all objects.
class Object
{
public:
    // Whether a ray intersects an object.
    virtual bool hit(const Ray& ray, float tMin, float tMax) const = 0;


private:
    // Material to use for the object.
    std::shared_ptr<Material> m_material;
};


} // namespace Raytracer


#endif