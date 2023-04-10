#include "image_texture.h"

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>


namespace Raytracer
{


ImageTexture::ImageTexture(const std::string& path) noexcept
{
    m_image = std::make_unique<Image>(path);
}


glm::vec3 ImageTexture::colourAt(float u, float v, const glm::vec3& p) const
{
    // convert to image coordinates
    float x = static_cast<int>(glm::clamp(u, 0.0f, 0.9999f) * m_image->width());
    float y = static_cast<int>(glm::clamp(v, 0.0f, 0.9999f) * m_image->height());

    return m_image->get(x, y);
}


} // namespace Raytracer