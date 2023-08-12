#pragma once

#include <cstdint>

namespace texplr {

typedef uint32_t EventIndex;

struct EventCounter {
    static uint32_t count;
};

struct Event {
};

template <class EventType>
EventIndex GetEventId()
{
    static EventIndex id = EventCounter::count++;
    return id;
}

} // namespace texplr
