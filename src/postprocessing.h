#ifndef POSTPROCESSING_H__WjMsLmYDMZ
#define POSTPROCESSING_H__WjMsLmYDMZ

#include <glm/glm.hpp>


namespace Raytracer
{


// Maps HDR values to LDR values via the ACES Filmic Tone Mapping Curve.
constexpr glm::vec3 toneMap(glm::vec3 colour);


constexpr glm::vec3 toneMap(glm::vec3 colour){
    // constexpr float a = 2.51f;
    // constexpr float b = 0.03f;
    // constexpr float c = 2.43f;
    // constexpr float d = 0.59f;
    // constexpr float e = 0.14f;
    
    // return (colour * (a * colour + b)) / (colour * (c * colour + d) + e);
    return colour;
}


} // namespace Raytracer


#endif