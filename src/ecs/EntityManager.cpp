#include <ecs/EntityManager.hpp>

namespace texplr {

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
    if (m_lastEntity != 0) {
        for (EntityHandle i = 1; i <= m_lastEntity; i++) {
            if (m_freeEntities.contains(i)) {
                continue;
            }

            destroyEntity(i);
        }
    }

    m_freeEntities.clear();
}

EntityHandle EntityManager::createEntity()
{
    if (m_freeEntities.empty()) {
        return ++m_lastEntity;
    }

    EntityHandle entityHandle = *m_freeEntities.begin();
    m_freeEntities.erase(m_freeEntities.begin());

    return entityHandle;
}

void EntityManager::destroyEntity(EntityHandle entity)
{
    if (entity == m_lastEntity) {
        m_lastEntity--;
        return;
    }

    m_freeEntities.insert(entity);
    // TODO: Emit a event.
}

} // namespace texplr
