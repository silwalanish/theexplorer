#pragma once

#include <memory>
#include <set>

#include <core/EventBus.hpp>
#include <ecs/EntityHandle.hpp>
#include <ecs/Events.hpp>

namespace texplr {

class World;

class System {
public:
    System();
    virtual ~System();

    virtual void init() = 0;
    virtual void update(float deltaTime);

    void registerEntity(EntityHandle handle);
    void unregisterEntity(EntityHandle handle);

    void registerWorld(World* world);

protected:
    std::set<EntityHandle> m_registeredEntities;
    World* m_world;
    std::shared_ptr<EventBus> m_eventBus;
};

} // namespace texplr
