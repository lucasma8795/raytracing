#ifndef IMAGE_TEXTURE_H__OZLj13LxNf
#define IMAGE_TEXTURE_H__OZLj13LxNf

#include "../image.h"
#include "../texture.h"

#include <memory>
#include <string>

#include <glm/glm.hpp>


namespace Raytracer
{


class ImageTexture: public Texture
{
public:
    // Create an image texture.
    explicit ImageTexture(const std::string& path) noexcept;

    // Returns the colour of the image texture at the given coordinates.
    virtual glm::vec3 colourAt(float u, float v, const glm::vec3& p) const override;


private:
    std::unique_ptr<Image> m_image; // Image buffer.
};


}


#endif