#include "image.h"

#include "utils.h"

#include <memory>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>


namespace Raytracer
{


Image::Image(int width, int height) noexcept
    : m_width{width}, m_height{height}
{
    // allocate memory for pixels
    m_pixels = std::make_unique_for_overwrite<glm::vec3[]>(width * height);
}


Image::Image(const std::string& path) noexcept
{
    SDL_Surface* surface = IMG_Load(path.c_str());

    if (surface == nullptr)
        fatal("Failed to load image!");

    // allocate memory for pixels
    m_width = surface->w;
    m_height = surface->h;
    m_pixels = std::make_unique_for_overwrite<glm::vec3[]>(m_width * m_height);

    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            glm::vec3 colour;

            // pointer to pixel in SDL texture
            int bpp = surface->format->BytesPerPixel;
            uint8_t* base = static_cast<uint8_t*>(surface->pixels) + y * surface->pitch + x * bpp;

            colour.r = *base++ / 255.0f;
            colour.g = *base++ / 255.0f;
            colour.b = *base++ / 255.0f;

            m_pixels[y * m_width + x] = colour;
        }
    }

    SDL_FreeSurface(surface); // get rid of surface
}


} // namespace Raytracer