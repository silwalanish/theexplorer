#pragma once

#include <components/AutoRotation.hpp>
#include <components/Transform.hpp>
#include <ecs/ScopedSystem.hpp>

namespace texplr {

class Rotator : public virtual ScopedSystem<Transform, AutoRotation> {
public:
    virtual void OnInit() override;
    virtual void OnUpdate(float deltaTime) override;
};

} // namespace texplr
