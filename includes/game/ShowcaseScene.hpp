#pragma once

#include <core/Scene.hpp>
#include <scripting/ScriptableWorld.hpp>
#include <systems/DebugRenderer.hpp>
#include <systems/SceneRenderer.hpp>

namespace texplr {

class ShowcaseScene : public virtual Scene {
public:
    ShowcaseScene(std::shared_ptr<EventBus> eventBus);

    virtual void OnInit() override;
    virtual void OnUpdate(float deltaTime) override;

    EntityHandle getSun() const;
    EntityHandle getActiveCamera() const;
    std::shared_ptr<ScriptableWorld> getWorld() const;

    void setSun(EntityHandle sun);
    void setActiveCamera(EntityHandle camera);

private:
    bool m_debugRender = false;
    EntityHandle m_activeCamera = 0;
    EntityHandle m_sun = 0;
    std::shared_ptr<SceneRenderer> m_renderer;
    std::shared_ptr<DebugRenderer> m_debugRenderer;
    std::shared_ptr<ScriptableWorld> m_world;

    void OnMouseDown(MouseButtonDownEvent* event);
    void OnMouseUp(MouseButtonUpEvent* event);
    void OnKeyUp(KeyUpEvent* event);
};

} // namespace texplr
