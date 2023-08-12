#pragma once

#include <core/EntityManager.hpp>
#include <core/EventBus.hpp>
#include <core/GameWindow.hpp>
#include <core/Input.hpp>
#include <core/SceneGraph.hpp>

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

    EntityHandle createEntity();
    void destroyEntity(EntityHandle handle);

    void addChild(const EntityHandle& parent, const EntityHandle& child);
    void removeChild(const EntityHandle& parent, const EntityHandle& child);

    EntityHandle getRoot() const;
    const std::set<EntityHandle>& getChildren(const EntityHandle& parent) const;
    EntityHandle getParent(const EntityHandle& child) const;

    std::shared_ptr<Input> getInputManager() const;
    std::shared_ptr<EventBus> getEventBus() const;
    std::shared_ptr<GameWindow> getWindow() const;
    std::shared_ptr<SceneGraph> getSceneGraph() const;

protected:
    bool m_isInitialized = false;
    Application* m_application;
    std::shared_ptr<SceneGraph> m_sceneGraph;
    std::unique_ptr<EntityManager> m_entityManager;

    std::shared_ptr<Input> m_inputManager;
    std::shared_ptr<EventBus> m_eventBus;
};

} // namespace texplr
