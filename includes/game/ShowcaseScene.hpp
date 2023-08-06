#pragma once

#include <core/Scene.hpp>
#include <systems/DebugRenderer.hpp>
#include <systems/SceneRenderer.hpp>

namespace texplr {

class ShowcaseScene : public virtual Scene {
public:
    ShowcaseScene(std::shared_ptr<EventBus> eventBus);

    virtual void OnInit() override;
    virtual void OnUpdate(float deltaTime) override;

private:
    bool m_debugRender = false;
    std::shared_ptr<SceneRenderer> m_renderer;
    std::shared_ptr<DebugRenderer> m_debugRenderer;

    void OnMouseDown(MouseButtonDownEvent* event);
    void OnMouseUp(MouseButtonUpEvent* event);
    void OnKeyUp(KeyUpEvent* event);
};

} // namespace texplr
