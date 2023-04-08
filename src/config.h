#ifndef CONFIG_H__UJ2uEkxQSH
#define CONFIG_H__UJ2uEkxQSH

#include <string>


namespace Raytracer
{

// Version numbers
const int VER_MAJ   = 0;
const int VER_MIN   = 0;
const int VER_PATCH = 0;

// Title of the window.
const std::string WINDOW_TITLE = "Raytracing";

// Width and height of the window.
const int WINDOW_WIDTH   = 900; // 3024;
const int WINDOW_HEIGHT  = 600; // 1984;
const float ASPECT_RATIO = static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT;

// Number of pixels.
const int NUM_PIXELS = WINDOW_WIDTH * WINDOW_HEIGHT;


} // namespace Raytracer


#endif