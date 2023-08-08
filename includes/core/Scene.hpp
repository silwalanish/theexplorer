#pragma once

#include <core/EventBus.hpp>
#include <core/GameWindow.hpp>
#include <core/Input.hpp>
#include <scripting/ScriptableWorld.hpp>

namespace texplr {

class Application;

class Scene {
public:
    Scene(std::shared_ptr<EventBus> eventBus);
    virtual ~Scene();

    Scene(const Scene& world) = delete;
    Scene& operator=(const Scene& world) = delete;

    void registerApplication(Application* application);

    void init();
    void update(float deltaTime);

    virtual void OnInit() = 0;
    virtual void OnUpdate(float deltaTime) = 0;

    std::shared_ptr<Input> getInputManager() const;
    std::shared_ptr<ScriptableWorld> getWorld() const;
    std::shared_ptr<EventBus> getEventBus() const;
    std::shared_ptr<GameWindow> getWindow() const;
    EntityHandle getSun() const;
    EntityHandle getActiveCamera() const;

    void setSun(EntityHandle sun);
    void setActiveCamera(EntityHandle camera);

protected:
    bool m_isInitialized = false;
    EntityHandle m_activeCamera = 0;
    EntityHandle m_sun = 0;
    Application* m_application;

    std::shared_ptr<Input> m_inputManager;
    std::shared_ptr<ScriptableWorld> m_world;
    std::shared_ptr<EventBus> m_eventBus;
};

} // namespace texplr
