#pragma once

#include <components/Transform.hpp>
#include <ecs/ScopedSystem.hpp>

namespace texplr {

class TransformSystem : public virtual ScopedSystem<Transform> {
public:
    virtual void OnInit() override;
    virtual void OnUpdate(float deltaTime) override;
};

} // namespace texplr
