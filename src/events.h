#ifndef EVENTS_H__ZRE0pCahEn
#define EVENTS_H__ZRE0pCahEn

#include <functional>
#include <string>

#include <glm/glm.hpp>


namespace Raytracer
{


// Event types and their required arguments.
namespace Events
{
    // test event
    struct Dummy { std::string msg; };

    // camera movements
    struct CameraTranslate { glm::vec3 dir; float dt; };
    struct CameraRotate {  }; // TODO!

    // window resize
    struct WindowResize { int width; int height; };
}


// Base event.
class BaseEvent
{
protected:
    static size_t getID();
};


// Templated event class from an event type.
template<typename EventType>
class Event: public BaseEvent
{
public:
    Event(const EventType& event) noexcept;

    static size_t getID();

    const EventType& m_eventType;
};


// Required type of callback.
// All callbacks MUST return void and have one parameter of type 'const EventType&'.
template<class EventType> using call_type = std::function<void(const EventType&)>;


// Functor to wrap the callback in order to store in a vector.
template<typename EventType>
class CallbackWrapper
{
public:
    CallbackWrapper(call_type<EventType> callable) noexcept;

    void operator()(const BaseEvent& event);

private:
    call_type<EventType> m_callable;
};


// Class to store and fire events.
class EventManager
{
public:
    // Subscribe to an event.
    template<typename EventType> void subscribe(call_type<EventType> callback);

    // Fire an event.
    template<typename EventType> void fire(const EventType& event);


private:
    std::vector<std::vector<call_type<BaseEvent>>> m_callbacks;
};


// Global event manager.
extern EventManager g_eventMgr;


template<typename EventType>
Event<EventType>::Event(const EventType& event) noexcept
    : m_eventType{event}
{}


template<typename EventType>
size_t Event<EventType>::getID()
{
    static size_t id = BaseEvent::getID();
    return id;
}


template<typename EventType>
CallbackWrapper<EventType>::CallbackWrapper(call_type<EventType> callable) noexcept
    : m_callable{callable}
{}


template<typename EventType>
void EventManager::subscribe(call_type<EventType> callback)
{
    size_t id = Event<EventType>::getID();

    // check if callbacks vector is large enough
    if (id >= m_callbacks.size())
        m_callbacks.resize(id + 1);

    m_callbacks[id].push_back(CallbackWrapper<EventType>(callback));
}


template<typename EventType>
void EventManager::fire(const EventType& event)
{
    Event<EventType> eventWrapper(event);
    size_t id = Event<EventType>::getID();
    
    // check if callbacks vector is large enough
    if (id >= m_callbacks.size())
        m_callbacks.resize(id + 1);

    for (auto& callback: m_callbacks[id])
        callback(eventWrapper);
}


template<typename EventType>
void CallbackWrapper<EventType>::operator()(const BaseEvent& event)
{
    // call the underlying function
    m_callable(static_cast<const Event<EventType>&>(event).m_eventType);
}


};


#endif