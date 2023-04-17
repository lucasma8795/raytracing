#ifndef IMAGE_H__9KxNHSAPz4
#define IMAGE_H__9KxNHSAPz4

#include <cassert>
#include <string>
#include <vector>

#include <glm/glm.hpp>


namespace Raytracer
{


// Simple implementation of an image buffer.
class Image
{
public:
    // Create a new image.
    explicit Image() noexcept;
    explicit Image(size_t width, size_t height) noexcept;
    explicit Image(const std::string& path) noexcept;

    // Reset the image to all black.
    void reset();

    // Get pixel colour at a given position.
    glm::vec3 get(size_t x, size_t y) const;
    // glm::vec3 get(float x, float y) const;

    // Add to pixel colour at a given position.
    void add(size_t x, size_t y, glm::vec3 colour);
    
    // Set pixel colour at a given position.
    void set(size_t x, size_t y, glm::vec3 colour);

    // Getter for width and height.
    size_t width() const;
    size_t height() const;


private:
    std::vector<glm::vec3> m_pixels;

    size_t m_width = 0U;  // Width of the image, in pixels.
    size_t m_height = 0U; // Height of the image, in pixels.
};


inline void Image::reset()
{
    // Fill all elements with black.
    std::fill(m_pixels.begin(), m_pixels.end(), glm::vec3{0.0f});
}


inline glm::vec3 Image::get(size_t x, size_t y) const
{
    return m_pixels.at(y * m_width + x);
}


// inline glm::vec3 Image::get(float x, float y) const
// {
//     // bilinear interpolation: TODO!
// }


inline void Image::set(size_t x, size_t y, glm::vec3 colour)
{
    m_pixels.at(y * m_width + x) = colour;
}


inline void Image::add(size_t x, size_t y, glm::vec3 colour)
{
    m_pixels.at(y * m_width + x) += colour;
}


inline size_t Image::width() const
{
    return m_width;
}


inline size_t Image::height() const
{
    return m_height;
}


} // namespace Raytracer


#endif