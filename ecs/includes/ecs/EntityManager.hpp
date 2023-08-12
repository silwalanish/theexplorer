#pragma once

#include <memory>
#include <set>

#include <core/EventBus.hpp>
#include <core/EntityHandle.hpp>

namespace texplr {

class EntityManager {
public:
    EntityManager(std::shared_ptr<EventBus> eventBus);
    ~EntityManager();

    EntityHandle createEntity();
    void destroyEntity(EntityHandle entity);

private:
    EntityHandle m_lastEntity = 0;
    std::set<EntityHandle> m_freeEntities;
    std::shared_ptr<EventBus> m_eventBus;
};

} // namespace texplr
