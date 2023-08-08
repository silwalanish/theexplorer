#pragma once

#include <ecs/Events.hpp>
#include <ecs/ScopedSystem.hpp>

#include <scripting/component/NativeScript.hpp>

namespace texplr {

class NativeScriptEngine : public virtual ScopedSystem<NativeScript> {
public:
    virtual void OnInit() override;
    virtual void OnUpdate(float deltaTime) override;
};

} // namespace texplr
