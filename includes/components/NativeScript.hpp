#pragma once

#include <vector>

#include <core/Script.hpp>
#include <ecs/Component.hpp>

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
