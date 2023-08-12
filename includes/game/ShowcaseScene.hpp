#pragma once

#include <renderer/DebugRenderer.hpp>
#include <renderer/RenderableScene.hpp>

namespace texplr {

class ShowcaseScene : public virtual RenderableScene {
public:
    ShowcaseScene(std::shared_ptr<EventBus> eventBus);
    virtual ~ShowcaseScene();

    virtual void OnInit() override;
    virtual void OnUpdate(float deltaTime) override;

private:
    bool m_debugRender = false;
    std::shared_ptr<DebugRenderer> m_debugRenderer;

    void OnMouseDown(MouseButtonDownEvent* event);
    void OnMouseUp(MouseButtonUpEvent* event);
    void OnKeyUp(KeyUpEvent* event);
};

} // namespace texplr
