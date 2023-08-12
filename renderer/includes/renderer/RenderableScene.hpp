#pragma once

#include <core/Scene.hpp>
#include <ecs/World.hpp>
#include <renderer/SceneRenderer.hpp>

namespace texplr {

class RenderableScene : public virtual Scene {
public:
    RenderableScene(std::shared_ptr<EventBus> eventBus);
    virtual ~RenderableScene();

    virtual void OnUpdate(float deltaTime) override;

    template <typename WorldType>
    std::shared_ptr<WorldType> createWorld()
    {
        std::shared_ptr<WorldType> world = std::make_shared<WorldType>(m_eventBus);
        world->registerToScene(this);

        m_renderer = world->registerSystem<SceneRenderer>();

        m_world = std::static_pointer_cast<World>(world);

        return world;
    }

    EntityHandle getSun() const;
    EntityHandle getActiveCamera() const;
    std::shared_ptr<World> getWorld() const;

    void setSun(EntityHandle sun);
    void setActiveCamera(EntityHandle camera);

protected:
    EntityHandle m_activeCamera = 0;
    EntityHandle m_sun = 0;
    std::shared_ptr<SceneRenderer> m_renderer;
    std::shared_ptr<World> m_world;
};

} // namespace texplr
