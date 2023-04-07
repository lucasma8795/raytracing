#include <cstdlib>

#include "window.h"

using namespace Raytracer;


int main()
{
    Window m_window;

    m_window.init();
    m_window.mainLoop();
}