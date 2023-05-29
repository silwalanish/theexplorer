#pragma once

#include <core/Scene.hpp>

namespace texplr {

class ShowcaseScene : public virtual Scene {
public:
    ShowcaseScene(std::shared_ptr<EventBus> eventBus);

    virtual void OnInit() override;
    virtual void OnUpdate(float deltaTime) override;

private:
};

} // namespace texplr
