#pragma once

#include <core/Scene.hpp>
#include <systems/SceneRenderer.hpp>

namespace texplr {

class ShowcaseScene : public virtual Scene {
public:
    ShowcaseScene(std::shared_ptr<EventBus> eventBus);

    virtual void OnInit() override;
    virtual void OnUpdate(float deltaTime) override;

private:
    std::shared_ptr<SceneRenderer> m_renderer;

    void OnMouseDown(MouseButtonDownEvent* event);
    void OnMouseUp(MouseButtonUpEvent* event);
};

} // namespace texplr
