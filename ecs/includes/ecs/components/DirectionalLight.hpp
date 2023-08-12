#pragma once

#include <core/Light.hpp>
#include <ecs/Component.hpp>

namespace texplr {

struct DirectionalLight : public Component<DirectionalLight> {
public:
    Light light;

    DirectionalLight() = default;
    DirectionalLight(const DirectionalLight&) = default;

    DirectionalLight(const Light& light)
        : light(light)
    {
    }
};

} // namespace texplr
