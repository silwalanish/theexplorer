#pragma once

#include <ecs/System.hpp>
#include <ecs/World.hpp>

namespace texplr {

template <typename... ComponentTypes>
class ScopedSystem : public virtual System {
public:
    virtual ~ScopedSystem()
    {
        if (m_eventBus) {
            m_eventBus->unsubscribe<ScopedSystem<ComponentTypes...>, EntityDestroyedEvent>(this);
            teardownEvents<ComponentTypes...>();
        }
    }

    void init() override
    {
        setupEvents<ComponentTypes...>();
        m_eventBus->subscribe(this, &ScopedSystem<ComponentTypes...>::OnEntityDestroyed);

        OnInit();
    }

    void update(float deltaTime) override
    {
        OnUpdate(deltaTime);
    }

    virtual void OnInit() { }
    virtual void OnUpdate(float deltaTime) { }

private:
    template <typename T>
    void OnComponentAdded(ComponentAddedEvent<T>* event)
    {
        if (m_world->hasAllComponent<ComponentTypes...>(event->entity)) {
            registerEntity(event->entity);
        }
    }

    template <typename T>
    void OnComponentRemoved(ComponentRemovedEvent<T>* event)
    {
        unregisterEntity(event->entity);
    }

    void OnEntityDestroyed(EntityDestroyedEvent* event)
    {
        unregisterEntity(event->entity);
    }

    template <typename ComponentType1>
    void setupEvents()
    {
        m_eventBus->subscribe<ScopedSystem<ComponentTypes...>, ComponentAddedEvent<ComponentType1>>(this, &ScopedSystem<ComponentTypes...>::OnComponentAdded);
        m_eventBus->subscribe<ScopedSystem<ComponentTypes...>, ComponentRemovedEvent<ComponentType1>>(this, &ScopedSystem<ComponentTypes...>::OnComponentRemoved);
    }

    template <typename ComponentType1, typename ComponentType2, typename... OtherComponentTypes>
    void setupEvents()
    {
        setupEvents<ComponentType1>();
        setupEvents<ComponentType2, OtherComponentTypes...>();
    }

    template <typename ComponentType1>
    void teardownEvents()
    {
        m_eventBus->unsubscribe<ScopedSystem<ComponentTypes...>, ComponentAddedEvent<ComponentType1>>(this);
        m_eventBus->unsubscribe<ScopedSystem<ComponentTypes...>, ComponentRemovedEvent<ComponentType1>>(this);
    }

    template <typename ComponentType1, typename ComponentType2, typename... OtherComponentTypes>
    void teardownEvents()
    {
        teardownEvents<ComponentType1>();
        teardownEvents<ComponentType2, OtherComponentTypes...>();
    }
};

} // namespace texplr
