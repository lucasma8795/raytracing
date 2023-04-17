#ifndef WINDOW_H__j1G2iTz7r8
#define WINDOW_H__j1G2iTz7r8

#include "image.h"

#include "camera.h"
#include "config.h"
#include "events.h"
#include "scene.h"

#include <chrono>
#include <unordered_map>
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

    // event handlers
    void onScreenshot(const Events::Screenshot& event);
    void onCameraTranslate(const Events::CameraTranslate& event);
    void onCameraRotate(const Events::CameraRotate& event);


private:
    Camera m_camera{VIEWPORT_WIDTH, VIEWPORT_HEIGHT}; // Rendering camera.

    Scene m_scene; // Scene to render.
    
    Image m_accumulated; // Accumulated image buffer.

    SDL_Texture* m_buffer;

    SDL_Event     m_event;    // Event emitted by SDL2.
    SDL_Window*   m_window;   // Instance of SDL2 window.
    SDL_Renderer* m_renderer; // Instance of SDL2 renderer.

    int m_frameIndex = 1; // Number of frames since last camera movement.

    bool m_quit = false; // Whether to kill the window as soon as possible.

    std::unordered_map<SDL_Keycode, bool> m_keyboard; // Whether a key is pressed.
};


} // namespace Raytracer


#endif