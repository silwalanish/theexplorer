#pragma once

#include <core/EventBus.hpp>
#include <ecs/World.hpp>

namespace texplr {

class Scene {
public:
    Scene(std::shared_ptr<EventBus> eventBus);
    virtual ~Scene();

    Scene(const Scene& world) = delete;
    Scene& operator=(const Scene& world) = delete;

    void init();
    void update(float deltaTime);

    virtual void OnInit() = 0;
    virtual void OnUpdate(float deltaTime) = 0;

    std::shared_ptr<World> getWorld() const;
    std::shared_ptr<EventBus> getEventBus() const;
    EntityHandle getActiveCamera() const;

    void setActiveCamera(EntityHandle camera);

protected:
    bool m_isInitialized = false;
    EntityHandle m_activeCamera = 0;

    std::shared_ptr<World> m_world;
    std::shared_ptr<EventBus> m_eventBus;
};

} // namespace texplr
