#ifndef IMAGE_H__9KxNHSAPz4
#define IMAGE_H__9KxNHSAPz4

#include <cassert>
#include <cstring> // for memset()
#include <memory>

#include <glm/glm.hpp>


namespace Raytracer
{


// Simple implementation of an image buffer.
class Image
{
public:
    // Create a new image with specified width and height.
    explicit Image(int width, int height) noexcept;

    // Delete copy constructor and assignment operator.
    Image(const Image&) = delete;
    Image& operator=(Image const&) = delete;

    // Reset the image to all black.
    void reset();

    // Get pixel color at a given position.
    glm::vec3 get(int x, int y);
    
    // Set pixel color at a given position.
    void set(int x, int y, glm::vec3 color);


private:
    std::unique_ptr<glm::vec3[]> m_pixels;

    int m_width;  // Width of the image, in pixels.
    int m_height; // Height of the image, in pixels.
};


inline void Image::reset()
{
    // Fill all elements with black.
    std::fill_n(m_pixels.get(), m_width * m_height, glm::vec3{0.0f});
}


inline glm::vec3 Image::get(int x, int y)
{
    // Bounds checking
    assert(x >= 0 && x < m_width && y >= 0 && y < m_height);

    return m_pixels[y * m_width + x];
}


inline void Image::set(int x, int y, glm::vec3 color)
{
    m_pixels[y * m_width + x] = color;
}


} // namespace Raytracer


#endif