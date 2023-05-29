#pragma once

#include <set>

#include <ecs/EntityHandle.hpp>

namespace texplr {

class EntityManager {
public:
    EntityManager();
    ~EntityManager();

    EntityHandle createEntity();
    void destroyEntity(EntityHandle entity);

private:
    EntityHandle m_lastEntity = 0;
    std::set<EntityHandle> m_freeEntities;
};

} // namespace texplr
