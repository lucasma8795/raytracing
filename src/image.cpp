#include "image.h"

#include <memory>

#include <glm/glm.hpp>


namespace Raytracer
{


Image::Image(int width, int height) noexcept
    : m_width{width}, m_height{height}
{
    // Allocate memory for 1D array of pixels.
    m_pixels = std::make_unique_for_overwrite<glm::vec3[]>(width * height);
}


} // namespace Raytracer