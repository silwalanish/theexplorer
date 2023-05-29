#pragma once

#include <algorithm>
#include <map>
#include <vector>

#include <core/Event.hpp>

namespace texplr {

class EventHandler {
public:
    virtual void dispatch(Event* event)
    {
    }
};

template <class T, class EventType>
class MemberEventHandler : public virtual EventHandler {
public:
    typedef void (T::*MemberFunction)(EventType*);

    MemberEventHandler(T* instance, MemberFunction handler)
        : m_instance(instance)
        , m_handler(handler)
    {
    }

    virtual void dispatch(Event* event) override
    {
        call(static_cast<EventType*>(event));
    }

private:
    T* m_instance;
    MemberFunction m_handler;

    void call(EventType* event)
    {
        (m_instance->*m_handler)(event);
    }
};

class EventBus {
public:
    typedef std::vector<EventHandler*> HandlerList;

    EventBus()
    {
    }

    ~EventBus()
    {
    }

    template <class T, typename EventType>
    void subscribe(T* instance, void (T::*handler)(EventType*))
    {
        EventIndex eventType = GetEventId<EventType>();
        HandlerList* handlers = m_handlers[eventType];

        if (handlers == nullptr) {
            handlers = new HandlerList();
            m_handlers[eventType] = handlers;
        }

        MemberEventHandler<T, EventType>* eventHandler = new MemberEventHandler<T, EventType>(instance, handler);
        handlers->push_back(eventHandler);

        std::map<EventIndex, EventHandler*>* instanceHandlers = m_instanceHandlers[static_cast<void*>(instance)];
        if (instanceHandlers == nullptr) {
            instanceHandlers = new std::map<EventIndex, EventHandler*>();
            m_instanceHandlers[static_cast<void*>(instance)] = instanceHandlers;
        }

        instanceHandlers->insert_or_assign(eventType, static_cast<EventHandler*>(eventHandler));
    }

    template <class T, typename EventType>
    void unsubscribe(T* instance)
    {
        EventIndex eventType = GetEventId<EventType>();
        HandlerList* handlers = m_handlers[eventType];
        std::map<EventIndex, EventHandler*>* instanceHandlers = m_instanceHandlers[static_cast<void*>(instance)];

        if (instanceHandlers == nullptr || handlers == nullptr) {
            return;
        }

        EventHandler* handler = (*instanceHandlers)[eventType];
        if (handler != nullptr) {
            handlers->erase(std::find(handlers->begin(), handlers->end(), handler));
            instanceHandlers->erase(eventType);
        }
    }

    template <typename EventType>
    void notify(EventType* event)
    {
        HandlerList* handlers = m_handlers[GetEventId<EventType>()];

        if (handlers == nullptr) {
            return;
        }

        for (auto& handler : *handlers) {
            if (handler != nullptr) {
                handler->dispatch(event);
            }
        }
    }

private:
    std::map<void*, std::map<EventIndex, EventHandler*>*> m_instanceHandlers;
    std::map<EventIndex, HandlerList*> m_handlers;
};

} // namespace texplr
