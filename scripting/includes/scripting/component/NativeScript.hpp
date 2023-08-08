#pragma once

#include <memory>
#include <vector>

#include <ecs/Component.hpp>

#include <scripting/Script.hpp>

namespace texplr {

struct NativeScript : public Component<NativeScript> {
    std::vector<std::shared_ptr<Script>> scripts;

    NativeScript() = default;
    NativeScript(const NativeScript& cam) = default;
    NativeScript(std::vector<std::shared_ptr<Script>> scripts)
        : scripts(scripts)
    {
    }
};

} // namespace texplr
