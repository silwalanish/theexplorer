#pragma once

#include <cstdint>

namespace texplr {

typedef uint32_t ComponentIndex;

struct ComponentCounter {
    static uint32_t count;
};

template <typename T>
struct Component {
    static inline ComponentIndex GetId()
    {
        static ComponentIndex id = ComponentCounter::count++;
        return id;
    }
};

} // namespace texplr
