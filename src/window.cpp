#include "window.h"

#include "config.h"
#include "events.h"
#include "image.h"
#include "postprocessing.h"
#include "scenes/test_scene.h"
#include "scenes/planets.h"
#include "utils.h"

#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// #include <omp.h>


namespace Raytracer
{


Window::Window() noexcept
{
    // Initialize image buffer.
    m_accumulated = Image(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Scene selection.
    m_scene = planets();

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
        0 // SDL_WINDOW_FULLSCREEN
    );
    if (!m_window)
        fatal("SDL2 window failed to initialize!");

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer)
        fatal("SDL2 renderer failed to initialize!");

    // Create streaming texture for copying to renderer.
    m_buffer = SDL_CreateTexture(
        m_renderer,
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
        WINDOW_WIDTH, WINDOW_HEIGHT
    );

    // Set logging decimal place format.
    std::cout << std::fixed << std::setprecision(3);

    // Set program start timestamp.
    m_start = std::chrono::high_resolution_clock::now();
}


void Window::mainLoop()
{
    while (true)
    {
        handleEvents();
        update();
        if (m_quit) return;

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

    m_quit = true;
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
            m_accumulated.add(x, y, m_scene.raytrace(cameraRay));
        }
    }

    uint64_t end = SDL_GetPerformanceCounter();

    float dt = (end - start) / static_cast<float>(SDL_GetPerformanceFrequency());
    std::cout << "render: " << dt * 1000.0f << "ms / ";
}


void Window::display()
{
    uint64_t start = SDL_GetPerformanceCounter();

    void* pixels;
    int pitch;

    SDL_LockTexture(m_buffer, NULL, &pixels, &pitch);

    // loop over each pixel
    for (int y = 0; y < WINDOW_HEIGHT; ++y)
    {
        // pointer to pixel in SDL texture
        uint8_t* base = static_cast<uint8_t*>(pixels) + y * pitch;

        for (int x = 0; x < WINDOW_WIDTH; ++x)
        {
            // map [0, 1) to [0, 255]
            glm::vec3 colour = m_accumulated.get(x, y) * (1.0f / m_frameIndex);
            colour = glm::min(toneMap(colour), 0.9999f) * 256.0f;

            // RGBA8888 format
            *base++ = SDL_ALPHA_OPAQUE;
            *base++ = static_cast<uint8_t>(colour.b);
            *base++ = static_cast<uint8_t>(colour.g);
            *base++ = static_cast<uint8_t>(colour.r);
        }
    }

    SDL_UnlockTexture(m_buffer);
    SDL_RenderCopy(m_renderer, m_buffer, NULL, NULL);
    SDL_RenderPresent(m_renderer);

    uint64_t end = SDL_GetPerformanceCounter();

    float dt = (end - start) / static_cast<float>(SDL_GetPerformanceFrequency());
    std::cout << "display: " << dt * 1000.0f << "ms" << std::endl;

    ++m_frameIndex;
}


void Window::handleEvents()
{
    // SDL_WaitEvent(&m_event);
    SDL_PollEvent(&m_event);

    switch (m_event.type)
    {
        case SDL_QUIT:
            quit();
            break;

        case SDL_KEYDOWN:
            m_keyboard[m_event.key.keysym.sym] = true;
            break;

        case SDL_KEYUP:
            m_keyboard[m_event.key.keysym.sym] = false;
            break;
    }
}


void Window::update()
{
    uint64_t start = SDL_GetPerformanceCounter();

    if (m_keyboard[SDLK_ESCAPE])
        quit();

    if (m_keyboard[SDLK_w])
        EventMgr.fire(Event::CAMERA_MOVE);

    uint64_t end = SDL_GetPerformanceCounter();

    float dt = (end - start) / static_cast<float>(SDL_GetPerformanceFrequency());
    std::cout << "update: " << dt * 1000.0f << "ms / ";
}


} // namespace Raytracer