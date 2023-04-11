#include <cstdlib>

#include "window.h"

using namespace Raytracer;


int main()
{
    srand(920112); // For reproducibility

    Window m_window;

    m_window.init();
    m_window.mainLoop();

    return EXIT_SUCCESS;
}