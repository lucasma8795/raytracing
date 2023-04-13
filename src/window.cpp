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

#include <glm/gtx/norm.hpp>


namespace Raytracer
{


Window::Window() noexcept
{
    // Initialize image buffer.
    m_accumulated = Image(VIEWPORT_WIDTH, VIEWPORT_HEIGHT);

    // Scene selection.
    m_scene = testScene();

    // Initialize the SDL library.
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        fatal("SDL failed to initialize!");

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        fatal("SDL_image failed to initialize!");

    // Set SDL render quality to maximum.
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    
    // Create window and renderer.
    m_window = SDL_CreateWindow(
        PROJECT_TITLE.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        VIEWPORT_WIDTH, VIEWPORT_HEIGHT,
        IS_FULLSCREEN ? SDL_WINDOW_FULLSCREEN : 0
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
        VIEWPORT_WIDTH, VIEWPORT_HEIGHT
    );

    // Set logging decimal place format.
    std::cout << std::fixed << std::setprecision(3);

    // Bind events.
    g_eventMgr.subscribe(Event::CAMERA_TRANSLATE, [this](glm::vec3 dir, float dt) {
        m_frameIndex = 1;
        m_accumulated.reset();
    });

    g_eventMgr.subscribe(Event::SCREENSHOT, [this]() {
        screenshot("out.png");
    });
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
    for (int y = 0; y < VIEWPORT_HEIGHT; ++y)
    {
        for (int x = 0; x < VIEWPORT_WIDTH; ++x)
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
    for (int y = 0; y < VIEWPORT_HEIGHT; ++y)
    {
        // pointer to pixel in SDL texture
        uint8_t* base = static_cast<uint8_t*>(pixels) + y * pitch;

        for (int x = 0; x < VIEWPORT_WIDTH; ++x)
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
    auto newTime = std::chrono::high_resolution_clock::now();
    float dt = (newTime - m_oldTime).count() * 1e-9; // ns to s;
    m_oldTime = newTime;

    glm::vec3 velocity{0.0f};

    if (m_keyboard[SDLK_ESCAPE])
        quit();

    if (m_keyboard[SDLK_p])
    {
        g_eventMgr.fire(Event::SCREENSHOT);
        quit();
    }

    if (m_keyboard[SDLK_w])       velocity += DIR_FRONT;
    if (m_keyboard[SDLK_s])       velocity += DIR_BACK;
    if (m_keyboard[SDLK_a])       velocity += DIR_LEFT;
    if (m_keyboard[SDLK_d])       velocity += DIR_RIGHT;
    if (m_keyboard[SDLK_SPACE])   velocity += DIR_UP;
    if (m_keyboard[SDLK_LSHIFT])  velocity += DIR_DOWN;
    
    if (velocity != glm::vec3{0.0f})
        g_eventMgr.fire(Event::CAMERA_TRANSLATE, velocity, dt);
}


void Window::screenshot(const std::string& path)
{
    // create surface
    SDL_Surface *screenshot = SDL_CreateRGBSurface(
        0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, 32,
        0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000
    );
    if (screenshot == nullptr)
        fatal("Error while creating screenshot surface!");

    // copy pixels to surface
    if (SDL_MUSTLOCK(screenshot)) SDL_LockSurface(screenshot);
    SDL_RenderReadPixels(
        m_renderer, NULL, 0, screenshot->pixels, screenshot->pitch
    );
    if (SDL_MUSTLOCK(screenshot)) SDL_UnlockSurface(screenshot);

    // save image
    IMG_SavePNG(screenshot, path.c_str());
    SDL_FreeSurface(screenshot);
}


} // namespace Raytracer