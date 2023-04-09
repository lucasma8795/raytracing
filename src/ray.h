#ifndef RAY_H__Die6t85B89
#define RAY_H__Die6t85B89

#include <glm/glm.hpp>


namespace Raytracer
{


// Simple implementation of a light ray.
class Ray
{
public:
    // Construct a new ray.
    explicit Ray(glm::vec3 origin, glm::vec3 dir) noexcept;
    explicit Ray() noexcept;

    // Returns origin + t * dir.
    glm::vec3 at(float t) const;

    // Getters for origin and direction.
    glm::vec3 origin() const;
    glm::vec3 dir() const;


private:
    glm::vec3 m_orig; // Origin of the ray.
    glm::vec3 m_dir;  // Direction that the ray is pointing.
};


inline glm::vec3 Ray::at(float t) const
{
    return m_orig + t * m_dir;
}


inline glm::vec3 Ray::origin() const
{
    return m_orig;
}


inline glm::vec3 Ray::dir() const
{
    return m_dir;
}


} // namespace Raytracer


#endif