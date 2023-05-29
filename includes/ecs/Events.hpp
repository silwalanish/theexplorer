#pragma once

#include <ecs/EntityHandle.hpp>

namespace texplr {

struct EntityDestroyedEvent : public Event {
    const EntityHandle entity;

    EntityDestroyedEvent(EntityHandle entity)
        : entity(entity)
    {
    }
};

} // namespace texplr
