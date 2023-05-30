#pragma once

#include <map>
#include <memory>
#include <utility>
#include <vector>

#include <core/EventBus.hpp>
#include <ecs/Component.hpp>
#include <ecs/ComponentManager.hpp>
#include <ecs/EntityHandle.hpp>
#include <ecs/EntityManager.hpp>
#include <ecs/System.hpp>

namespace texplr {

class Scene;

class World {
public:
    World(std::shared_ptr<EventBus> eventBus);
    ~World();

    World(const World& world) = delete;
    World& operator=(const World& world) = delete;

    void update(float deltaTime);

    template <typename SystemType, typename... SystemArgs>
    std::shared_ptr<SystemType> registerSystem(SystemArgs&&... args)
    {
        std::shared_ptr<SystemType> system = std::make_shared<SystemType>(std::forward<SystemArgs>(args)...);
        system->registerWorld(this);

        m_systems.push_back(system);

        return system;
    }

    EntityHandle createEntity();
    void destroyEntity(EntityHandle handle);

    template <typename ComponentType>
    void addComponent(EntityHandle handle, const ComponentType& component)
    {
        getComponentManager<ComponentType>()->add(handle, component);
    }

    template <typename ComponentType>
    ComponentType& getComponent(EntityHandle handle)
    {
        return getComponentManager<ComponentType>()->get(handle);
    }

    template <typename ComponentType>
    void removeComponent(EntityHandle handle)
    {
        getComponentManager<ComponentType>()->remove(handle);
    }

    template <typename ComponentType>
    bool hasComponent(EntityHandle handle)
    {
        return getComponentManager<ComponentType>()->has(handle);
    }

    template <typename ComponentType>
    bool hasAllComponent(EntityHandle handle)
    {
        return hasComponent<ComponentType>(handle);
    }

    template <typename ComponentType1, typename ComponentType2, typename... OtherComponentTypes>
    bool hasAllComponent(EntityHandle handle)
    {
        return hasComponent<ComponentType1>(handle) && hasAllComponent<ComponentType2, OtherComponentTypes...>(handle);
    }

    void registerToScene(Scene* scene);

    Scene* getScene();

    const Scene* getScene() const;
    std::shared_ptr<EventBus> getEventBus() const;

private:
    std::map<uint32_t, std::unique_ptr<BaseComponentManager>> m_componentManagers;
    std::unique_ptr<EntityManager> m_entityManager;
    std::vector<std::shared_ptr<System>> m_systems;
    std::shared_ptr<EventBus> m_eventBus;
    Scene* m_scene;

    template <typename ComponentType>
    ComponentManager<ComponentType>* getComponentManager()
    {
        if (m_componentManagers.find(ComponentType::GetId()) == m_componentManagers.end()) {
            m_componentManagers[ComponentType::GetId()] = std::make_unique<ComponentManager<ComponentType>>(m_eventBus);
        }

        return static_cast<ComponentManager<ComponentType>*>(m_componentManagers[ComponentType::GetId()].get());
    }
};

} // namespace texplr
