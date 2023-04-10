#include "window.h"

#include "config.h"
#include "image.h"
#include "utils.h"
#include "scenes/test_scene.h"

#include <cstdint>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/gtc/random.hpp>
// #include <omp.h>


namespace Raytracer
{


Window::Window() noexcept
{
    // Initialize image buffer.
    m_accumulated = std::make_unique<Image>(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Scene selection.
    m_scene = testScene();
}


void Window::init()
{
    // Initialize the SDL library.
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        fatal("SDL failed to initialize!");

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        fatal("SDL_image failed to initialize!");

    // Set SDL render quality to maximum.
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    
    // Create window and renderer.
    m_window = SDL_CreateWindow(
        WINDOW_TITLE.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        0
    );
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    // Create streaming texture for copying to renderer.
    m_buffer = SDL_CreateTexture(
        m_renderer,
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
        WINDOW_WIDTH, WINDOW_HEIGHT
    );
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
    // #pragma omp parallel for num_threads(10)
    for (int y = 0; y < WINDOW_HEIGHT; ++y)
    {
        for (int x = 0; x < WINDOW_WIDTH; ++x)
        {
            // Ray pointing from camera origin to screen coordinates.
            Ray cameraRay = m_camera.getRay(x, y);

            // Trace ray colour.
            m_accumulated->add(x, y, m_scene.raytrace(cameraRay));
        }
    }

    uint64_t end = SDL_GetPerformanceCounter();

    float dt = (end - start) / static_cast<float>(SDL_GetPerformanceFrequency());
    std::cout << "render time: " << dt * 1000.0f << "ms    ";
}


void Window::display()
{
    uint64_t start = SDL_GetPerformanceCounter();

    void* pixels;
    int pitch;

    SDL_LockTexture(m_buffer, NULL, &pixels, &pitch);

    // Loop over each pixel
    for (int y = 0; y < WINDOW_HEIGHT; ++y)
    {
        for (int x = 0; x < WINDOW_WIDTH; ++x)
        {
            // pointer to pixel in SDL texture
            uint8_t* base = static_cast<uint8_t*>(pixels) + (y * WINDOW_WIDTH + x) * 4;

            // map [0, 1) to [0, 255]
            glm::vec3 colour = m_accumulated->get(x, y) * (1.0f / m_frameIndex);
            glm::vec3 colourRGB = glm::clamp(colour, 0.0f, 0.9999f) * 256.0f;

            // TODO: divide the colour by the number of samples and gamma-correct for gamma=2.0.

            // RGBA8888 format
            *base++ = SDL_ALPHA_OPAQUE;                  // Alpha, 8 bits
            *base++ = static_cast<uint8_t>(colourRGB.b); // Blue, 8 bits
            *base++ = static_cast<uint8_t>(colourRGB.g); // Green, 8 bits
            *base++ = static_cast<uint8_t>(colourRGB.r); // Red, 8 bits
        }
    }

    SDL_UnlockTexture(m_buffer);
    SDL_RenderCopy(m_renderer, m_buffer, NULL, NULL);
    SDL_RenderPresent(m_renderer);

    uint64_t end = SDL_GetPerformanceCounter();

    float elapsed = (end - start) / static_cast<float>(SDL_GetPerformanceFrequency());
    std::cout << "display time: " << elapsed * 1000.0f << "ms" << std::endl;

    ++m_frameIndex;
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