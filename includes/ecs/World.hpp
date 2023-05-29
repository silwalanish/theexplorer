#pragma once

#include <map>
#include <memory>
#include <vector>

#include <ecs/Component.hpp>
#include <ecs/ComponentManager.hpp>
#include <ecs/EntityHandle.hpp>
#include <ecs/EntityManager.hpp>

namespace texplr {

class World {
public:
    World();
    ~World();

    void update(float deltaTime);

private:
    EntityManager m_entityManager;
    std::map<uint32_t, std::unique_ptr<BaseComponentManager>> m_componentManagers;

    EntityHandle m_activeCamera = 0;

    template <typename ComponentType>
    ComponentManager<ComponentType>* getComponentManager()
    {
        if (m_componentManagers.find(ComponentType::GetId()) == m_componentManagers.end()) {
            m_componentManagers[ComponentType::GetId()] = std::make_unique<ComponentManager<ComponentType>>();
        }

        return static_cast<ComponentManager<ComponentType>*>(m_componentManagers[ComponentType::GetId()].get());
    }

    friend class Entity;
};

} // namespace texplr
