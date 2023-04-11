#ifndef IMAGE_H__9KxNHSAPz4
#define IMAGE_H__9KxNHSAPz4

#include <cassert>
#include <cstring> // for memset()
#include <memory>
#include <string>

#include <glm/glm.hpp>


namespace Raytracer
{


// Simple implementation of an image buffer.
class Image
{
public:
    // Create a new image.
    explicit Image() noexcept;
    explicit Image(int width, int height) noexcept;
    explicit Image(const std::string& path) noexcept;

    // Delete copy constructor and assignment operator.
    Image(const Image&) = delete;
    Image& operator=(Image const&) = delete;

    // Reset the image to all black.
    void reset();

    // Get pixel colour at a given position.
    glm::vec3 get(int x, int y);

    // Add to pixel colour at a given position.
    void add(int x, int y, glm::vec3 colour);
    
    // Set pixel colour at a given position.
    void set(int x, int y, glm::vec3 colour);

    // Getter for width and height.
    int width();
    int height();


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


inline void Image::set(int x, int y, glm::vec3 colour)
{
    // Bounds checking
    assert(x >= 0 && x < m_width && y >= 0 && y < m_height);
    
    m_pixels[y * m_width + x] = colour;
}


inline void Image::add(int x, int y, glm::vec3 colour)
{
    // Bounds checking
    assert(x >= 0 && x < m_width && y >= 0 && y < m_height);
    
    m_pixels[y * m_width + x] += colour;
}


inline int Image::width()
{
    return m_width;
}


inline int Image::height()
{
    return m_height;
}


} // namespace Raytracer


#endif