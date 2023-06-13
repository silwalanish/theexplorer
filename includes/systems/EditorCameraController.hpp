#pragma once

#include <components/Camera.hpp>
#include <components/EditorControls.hpp>
#include <components/Transform.hpp>
#include <ecs/ScopedSystem.hpp>

namespace texplr {

class EditorCameraController : public virtual ScopedSystem<Transform, Camera, EditorControls> {
public:
    virtual void OnUpdate(float deltaTime) override;
};

} // namespace texplr
