#ifndef WINDOW_H__j1G2iTz7r8
#define WINDOW_H__j1G2iTz7r8

#include "image.h"

#include "camera.h"
#include "scene.h"

#include <chrono>
#include <map>
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
    
    // Main loop of the window. This operation is blocking.
    void mainLoop();

    // Kills the window.
    void quit();


private:
    void render();         // Render the scene.
    void display();        // Copy the image buffer to the window.
    void handleEvents();   // Handle SDL2 emitted events.
    void update();         // Updates program components.

    void screenshot(const std::string& path);     // Take a screenshot of the current screen


private:
    Camera m_camera; // Rendering camera.

    Scene m_scene; // Scene to render.
    
    // std::unique_ptr<Image> m_image; // Image buffer.
    Image m_accumulated; // Accumulated image buffer.

    SDL_Texture* m_buffer;

    SDL_Event     m_event;    // Event emitted by SDL2.
    SDL_Window*   m_window;   // Instance of SDL2 window.
    SDL_Renderer* m_renderer; // Instance of SDL2 renderer.

    int m_frameIndex = 1; // Number of frames since last camera movement.

    bool m_quit = false; // Whether to kill the window as soon as possible.

    std::chrono::high_resolution_clock::time_point m_oldTime
        = std::chrono::high_resolution_clock::now(); // Timestamp of last frame.

    std::map<SDL_Keycode, bool> m_keyboard; // Whether a key is pressed.
};


} // namespace Raytracer


#endif