#pragma once

#include <vector>

#include <ecs/Component.hpp>
#include <scripting/Script.hpp>

namespace texplr {

struct NativeScript : Component<NativeScript> {
    std::vector<Script*> scripts;

    NativeScript() = default;
    NativeScript(const NativeScript& cam) = default;
    NativeScript(std::vector<Script*> scripts)
        : scripts(scripts)
    {
    }
};

} // namespace texplr
