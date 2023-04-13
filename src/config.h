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
constexpr bool IS_FULLSCREEN = true;

// Window attributes.
constexpr int VIEWPORT_WIDTH  = 1512; // 3024;
constexpr int VIEWPORT_HEIGHT = 982; // 1984;
constexpr float ASPECT_RATIO  = static_cast<float>(VIEWPORT_WIDTH) / VIEWPORT_HEIGHT;

// Number of pixels.
constexpr int NUM_PIXELS = VIEWPORT_WIDTH * VIEWPORT_HEIGHT;

constexpr float CAMERA_MOVESPEED = 5.0f;


} // namespace Raytracer


#endif