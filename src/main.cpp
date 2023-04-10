#include <cstdlib>

#include "window.h"

using namespace Raytracer;


int main()
{
    Window m_window;

    m_window.init();
    m_window.mainLoop();
}

// #include <chrono>
// #include <glm/gtc/random.hpp>
// #include <iostream>
// #include <glm/gtx/norm.hpp>

// #include "random.h"


// int main()
// {
//     srand(0);

//     auto start = std::chrono::high_resolution_clock::now();

//     for (int i = 0; i < 10000000; ++i)
//     {
//         glm::vec3 r;
//         do
//         {
//             r = glm::vec3{linearRand(), linearRand(), linearRand()};
//         } while (r.x*r.x + r.y*r.y + r.z*r.z > 1.0f);
//     }

//     auto end = std::chrono::high_resolution_clock::now();

//     std::cout << (end - start).count() << " ns" << std::endl;

//     start = std::chrono::high_resolution_clock::now();

//     for (int i = 0; i < 10000000; ++i)
//     {
//         glm::vec3 r;
//         do
//         {
//             r = glm::vec3{linearRand(), linearRand(), linearRand()};
//         } while (glm::length2(r) > 1.0f);
//     }

//     end = std::chrono::high_resolution_clock::now();

//     std::cout << (end - start).count() << " ns" << std::endl;
// }