// #ifndef SOLID_H__BSjpudQs3F
// #define SOLID_H__BSjpudQs3F

// #include "../material.h"
// #include "../types.h"

// #include <glm/glm.hpp>


// namespace Raytracer
// {


// // A surface with a solid colour.
// class Solid: public Material
// {
// public:
//     // Create a solid material.
//     explicit Solid(glm::vec3 albedo) noexcept;

//     // Always does not scatter.
//     virtual bool scatter(
//         const Ray& incident, const HitPayload& payload, glm::vec3& attenuation, Ray& scatter
//     ) const override;

//     // Always emits its characteristic colour.
//     virtual glm::vec3 emitted(const glm::vec3& normal) const override;


// private:
//     // Characteristic colour of the solid material.
//     glm::vec3 m_albedo;
// };


// } // namespace Raytracer


// #endif