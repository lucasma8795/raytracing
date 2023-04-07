#ifndef RAY_H__Die6t85B89
#define RAY_H__Die6t85B89

#include <glm/glm.hpp>


namespace Raytracer
{


class Ray
{
public:
    explicit Ray(glm::vec3 origin, glm::vec3 dir) noexcept;


private:
    glm::vec3 m_orig; // Origin of the ray.
    glm::vec3 m_dir;  // Direction that the ray is pointing.
};


} // namespace Raytracer


#endif