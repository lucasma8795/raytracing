#ifndef CONFIG_H__UJ2uEkxQSH
#define CONFIG_H__UJ2uEkxQSH

#include <string>


namespace Raytracer
{

// Version numbers.
const int VER_MAJ   = 0;
const int VER_MIN   = 0;
const int VER_PATCH = 0;

// Project metadata.
const std::string PROJECT_TITLE  = "Raytracing";
const std::string PROJECT_AUTHOR = "Lucas Ma";

// Whether to use full screen
constexpr bool IS_FULLSCREEN = false;

// Window attributes.
constexpr size_t VIEWPORT_WIDTH  = 900; // 1512; // 3024;
constexpr size_t VIEWPORT_HEIGHT = 600; // 982; // 1984;
constexpr float ASPECT_RATIO  = static_cast<float>(VIEWPORT_WIDTH) / VIEWPORT_HEIGHT;

// Number of pixels.
constexpr int NUM_PIXELS = VIEWPORT_WIDTH * VIEWPORT_HEIGHT;

} // namespace Raytracer


#endif