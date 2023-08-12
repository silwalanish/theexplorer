#pragma once

#include <memory>

#include <core/EntityHandle.hpp>
#include <ecs/World.hpp>

#include <scripting/Script.hpp>
#include <scripting/component/NativeScript.hpp>

namespace texplr {

class ScriptableWorld : public virtual World {
public:
    ScriptableWorld(std::shared_ptr<EventBus> eventBus);
    ~ScriptableWorld();

    template <typename ScriptType, typename... Args>
    void addScript(EntityHandle handle, const Args&... args)
    {
        if (!hasComponent<NativeScript>(handle)) {
            addComponent<NativeScript>(handle, NativeScript {});
        }

        std::shared_ptr<Script> script = std::make_shared<ScriptType>(args...);
        script->init();
        script->attach(handle, this);

        getComponent<NativeScript>(handle).scripts.push_back(script);
    }
};

} // namespace texplr
