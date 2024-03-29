#include <core/EntityManager.hpp>

#include <core/Events.hpp>

namespace texplr {

EntityManager::EntityManager(std::shared_ptr<EventBus> eventBus)
    : m_eventBus(eventBus)
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
    EntityHandle entityHandle;
    if (m_freeEntities.empty()) {
        entityHandle = ++m_lastEntity;
    } else {
        entityHandle = *m_freeEntities.begin();
        m_freeEntities.erase(m_freeEntities.begin());
    }

    m_eventBus->notify(new EntityCreatedEvent(entityHandle));

    return entityHandle;
}

void EntityManager::destroyEntity(EntityHandle entity)
{
    if (entity == m_lastEntity) {
        m_lastEntity--;
    } else {
        m_freeEntities.insert(entity);
    }

    m_eventBus->notify(new EntityDestroyedEvent(entity));
}

} // namespace texplr
