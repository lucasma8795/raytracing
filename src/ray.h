#ifndef RAY_H__Die6t85B89
#define RAY_H__Die6t85B89

#include <glm/glm.hpp>


namespace Raytracer
{


class Ray
{
public:
    // Construct a new ray.
    explicit Ray(glm::vec3 origin, glm::vec3 dir) noexcept;

    // Returns origin + t * dir.
    glm::vec3 at(float t);


private:
    glm::vec3 m_orig; // Origin of the ray.
    glm::vec3 m_dir;  // Direction that the ray is pointing.
};


inline glm::vec3 Ray::at(float t)
{
    return m_orig + t * m_dir;
}


} // namespace Raytracer


#endif