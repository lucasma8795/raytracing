#ifndef EVENTS_H__ZRE0pCahEn
#define EVENTS_H__ZRE0pCahEn

#include <functional>
#include <map>
#include <vector>

#include <SDL2/SDL.h>


namespace Raytracer
{


enum class Event
{
    CAMERA_MOVE
};


// Simple event manager for translating hardware triggers to semantic events.
class EventManager
{
public:
    // Fire an event.
    template<typename... Args>
    void fire(Event event, Args... args);

    // Subscribe to an event.
    void subscribe(Event event, std::function<void()> callback);

    // Unsubscribe to an event.
    // template<typename... Args> void unsubscribe(Event event, std::function<void(Args...)> callback);


private:
    // Maps an event to a vector of functions.
    std::map<Event, std::vector<std::function<void()>>> m_delegates;
};


template<typename... Args>
inline void EventManager::fire(Event event, Args... args)
{
    for (auto callback: m_delegates[event])
    {
        callback(args...);
    }
}


inline void EventManager::subscribe(Event event, std::function<void()> callback)
{
    m_delegates[event].push_back(callback);
}


// Global event manager.
extern EventManager EventMgr;


} // namespace Raytracer::Input


#endif