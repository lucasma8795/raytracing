#ifndef EVENTS_H__ZRE0pCahEn
#define EVENTS_H__ZRE0pCahEn

#include "utils.h"

#include <any>
#include <functional>
#include <map>
#include <type_traits>
#include <vector>

#include <SDL2/SDL.h>


namespace Raytracer
{


enum class Event
{
    CAMERA_TRANSLATE
};


template <typename T>
struct identity
{
    typedef T type;
};


// Simple event manager for translating hardware triggers to semantic events.
class EventManager
{
public:
    // Fire an event.
    template<typename... Args> void fire(Event event, Args... args);

    // Subscribe to an event.
    template<typename... Args> void subscribe(Event event, std::function<void(Args...)> callback);
    template<typename T> void subscribe(Event event, T callback);

    // Unsubscribe to an event.
    // template<typename... Args> void unsubscribe(Event event, void callback(Args...));


private:
    // Maps an event to a vector of functions.
    std::map<Event, std::vector<std::function<void(std::any)>>> m_callbacks;
};


template<typename... Args>
inline void EventManager::fire(Event event, Args... args)
{
    std::tuple<Args...> tuple = std::make_tuple(args...);

    for (auto callback: m_callbacks[event])
    {
        callback(tuple);
    }
}


template<typename... Args>
inline void EventManager::subscribe(Event event, std::function<void(Args...)> callback)
{
    m_callbacks[event].emplace_back(
        [=](std::any args) -> void {
            auto tuple = std::any_cast<std::tuple<Args...>>(args);
            std::apply(callback, tuple);
        }
    );
}


template<typename T>
inline void EventManager::subscribe(Event event, T callback)
{
    subscribe(event, std::function(callback));
}


// Global event manager.
extern EventManager g_eventMgr;


} // namespace Raytracer::Input


#endif