#include "window.h"

#include "config.h"
#include "events.h"
#include "image.h"
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


using namespace std::placeholders;


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

    // Capture the mouse.
    // SDL_SetRelativeMouseMode(SDL_TRUE);
    
    // Create window and renderer.
    m_window = SDL_CreateWindow(
        PROJECT_TITLE.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        VIEWPORT_WIDTH, VIEWPORT_HEIGHT,
        (IS_FULLSCREEN ? SDL_WINDOW_FULLSCREEN : 0) | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
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
    if (!m_buffer)
        fatal("Failed to create SDL2 streaming texture buffer!");

    // Set logging decimal place format.
    std::cout << std::fixed << std::setprecision(3);

    // Bind events.
    g_eventMgr.subscribe<Events::CameraTranslate>(std::bind(&Window::onCameraTranslate, this, _1));
    g_eventMgr.subscribe<Events::CameraRotate>(std::bind(&Window::onCameraRotate, this, _1));
    g_eventMgr.subscribe<Events::Screenshot>(std::bind(&Window::onScreenshot, this, _1));
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
    for (size_t y = 0; y < VIEWPORT_HEIGHT; ++y)
    {
        for (size_t x = 0; x < VIEWPORT_WIDTH; ++x)
        {
            Ray cameraRay = m_camera.getRay(x, y);
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
    for (size_t y = 0; y < VIEWPORT_HEIGHT; ++y)
    {
        // pointer to pixel in SDL texture
        uint8_t* base = static_cast<uint8_t*>(pixels) + y * pitch;

        for (size_t x = 0; x < VIEWPORT_WIDTH; ++x)
        {
            // map [0, 1) to [0, 255]
            glm::vec3 colour = m_accumulated.get(x, y) * (1.0f / m_frameIndex);
            colour = glm::clamp(colour, 0.0f, 0.9999f) * 256.0f;

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

        case SDL_WINDOWEVENT_RESIZED:
            g_eventMgr.fire(Events::WindowResize{m_event.window.data1, m_event.window.data2});
            break;
    }
}


void Window::update()
{
    uint64_t start = SDL_GetPerformanceCounter();
    
    // calculate time since last frame
    static auto m_oldTime = std::chrono::high_resolution_clock::now();
    auto newTime = std::chrono::high_resolution_clock::now();
    float dt = (newTime - m_oldTime).count() * 1e-9; // ns to s
    m_oldTime = newTime;

    // direction of travel of camera
    glm::vec3 dir{0.0f};

    if (m_keyboard[SDLK_ESCAPE])
        quit();

    if (m_keyboard[SDLK_p])
        g_eventMgr.fire(Events::Screenshot{"out.png"});

    if (m_keyboard[SDLK_w])       dir += DIR_FRONT;
    if (m_keyboard[SDLK_s])       dir += DIR_BACK;
    if (m_keyboard[SDLK_a])       dir += DIR_LEFT;
    if (m_keyboard[SDLK_d])       dir += DIR_RIGHT;
    if (m_keyboard[SDLK_SPACE])   dir += DIR_UP;
    if (m_keyboard[SDLK_LSHIFT])  dir += DIR_DOWN;
    
    if (dir != glm::vec3{0.0f})
        g_eventMgr.fire(Events::CameraTranslate{glm::normalize(dir), dt});

    if (m_keyboard[SDLK_RIGHT])
        g_eventMgr.fire(Events::CameraRotate{DIR_RIGHT, dt});
    else if (m_keyboard[SDLK_LEFT])
        g_eventMgr.fire(Events::CameraRotate{DIR_LEFT, dt});

    g_eventMgr.fire(Events::Update{});

    uint64_t _end = SDL_GetPerformanceCounter();

    float t = (_end - start) / static_cast<float>(SDL_GetPerformanceFrequency());
    std::cout << "update: " << t * 1000.0f << "ms / ";
}


void Window::onScreenshot(const Events::Screenshot& event)
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
    IMG_SavePNG(screenshot, event.path.c_str());
    SDL_FreeSurface(screenshot);

    quit();
}


void Window::onCameraTranslate(const Events::CameraTranslate& event)
{
    // reset accumulation
    m_frameIndex = 1;
    m_accumulated.reset();
}


void Window::onCameraRotate(const Events::CameraRotate& event)
{
    // reset accumulation
    m_frameIndex = 1;
    m_accumulated.reset();
}


void Window::onWindowResize(const Events::WindowResize& event)
{
    // reset accumulation
    m_frameIndex = 1;
    m_accumulated.reset();
}


} // namespace Raytracer