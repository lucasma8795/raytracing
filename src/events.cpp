#include "events.h"


namespace Raytracer
{


EventManager g_eventMgr;


size_t BaseEvent::getID()
{
    static size_t count = 0;
    return count++;
}


} // namespace Raytracer