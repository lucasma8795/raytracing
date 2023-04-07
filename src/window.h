#ifndef WINDOW_H__j1G2iTz7r8
#define WINDOW_H__j1G2iTz7r8

#include "image.h"

#include "camera.h"
#include "scene.h"

#include <memory>

#include <SDL2/SDL.h>


namespace Raytracer
{


// Simple wrapper around SDL2 API.
class Window
{
public:
    // Create a new window.
    Window() noexcept;

    // Delete copy constructor and assignment operator.
    Window(const Window&) = delete;
    Window& operator=(Window const&) = delete;

    // Initialize the window.
    void init();

    // Main loop of the window. This operation is blocking.
    void mainLoop();

    // Kills the window.
    void quit() __attribute__((noreturn));


private:
    void render();  // Render the scene.
    void display(); // Copy the image buffer to the window.

    void handleEvents(); // Handle SDL2 emitted events.


private:
    Camera m_camera; // Rendering camera.

    Scene m_scene; // Scene to render.
    
    std::unique_ptr<Image> m_image; // Image buffer.

    SDL_Event     m_event;    // Event emitted by SDL2.
    SDL_Window*   m_window;   // Instance of SDL2 window.
    SDL_Renderer* m_renderer; // Instance of SDL2 renderer.
};


} // namespace Raytracer


#endif