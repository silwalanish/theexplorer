#pragma once

#include <components/NativeScript.hpp>
#include <ecs/Events.hpp>
#include <ecs/ScopedSystem.hpp>

namespace texplr {

class Scripting : public virtual ScopedSystem<NativeScript> {
public:
    virtual void OnInit() override;
    virtual void OnUpdate(float deltaTime) override;
};

} // namespace texplr
