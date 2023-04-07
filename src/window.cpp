#include "window.h"

#include "config.h"
#include "image.h"
#include "utils.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <glm/gtc/random.hpp>
#include <omp.h>


namespace Raytracer
{


Window::Window() noexcept
{
    // Initialize image buffer.
    m_image = std::make_unique<Image>(WINDOW_WIDTH, WINDOW_HEIGHT);
}


void Window::init()
{
    // Initialize the SDL library.
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fatal("SDL failed to initialize!");
    }

    // Set SDL render quality to maximum.
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    
    // Create window and renderer.
    m_window = SDL_CreateWindow(
        WINDOW_TITLE.data(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        0
    );
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
}


void Window::mainLoop()
{
    while (true)
    {
        handleEvents();
        render();
        display();
    }
}


void Window::quit()
{
    // Kill the SDL library.
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window); 
    SDL_Quit();

    std::exit(EXIT_SUCCESS);
}


void Window::render()
{
    uint64_t start = SDL_GetPerformanceCounter();

    // Loop over each pixel
    #pragma omp parallel for num_threads(10)
    for (int x = 0; x < WINDOW_WIDTH; ++x)
    {
        for (int y = 0; y < WINDOW_HEIGHT; ++y)
        {
            // Ray pointing from camera origin to screen coordinates.
            Ray cameraRay = m_camera.getRay(x, y);
            // Trace ray colour.
            m_image->set(x, y, m_scene.raytrace(cameraRay));
        }
    }

    uint64_t end = SDL_GetPerformanceCounter();

    float elapsed = (end - start) / static_cast<float>(SDL_GetPerformanceFrequency());
    std::cout << "frame time: " << elapsed * 1000.0f << "ms" << std::endl;
}


void Window::display()
{
    // Loop over each pixel
    for (int x = 0; x < WINDOW_WIDTH; ++x)
    {
        for (int y = 0; y < WINDOW_HEIGHT; ++y)
        {
            // quantize [0, 1) to [0, 255]
            glm::vec3 colorRGB = m_image->get(x, y) * 255.999f;
            uint8_t r = static_cast<uint8_t>(colorRGB.x);
            uint8_t g = static_cast<uint8_t>(colorRGB.y);
            uint8_t b = static_cast<uint8_t>(colorRGB.z);

            // set new pixel colour
            SDL_SetRenderDrawColor(m_renderer, r, g, b, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawPoint(m_renderer, x, y);
        }
    }

    SDL_RenderPresent(m_renderer);
}


void Window::handleEvents()
{
    // Wait for an SDL event.
    // SDL_WaitEvent(&m_event);
    SDL_PollEvent(&m_event);

    switch (m_event.type)
    {
        case SDL_QUIT:
            quit();
        

    }
}


} // namespace Raytracer