#pragma once

#include <ecs/Component.hpp>

namespace texplr {

struct AutoRotation : public Component<AutoRotation> {
    float speed;

    AutoRotation() = default;
    AutoRotation(const AutoRotation&) = default;

    AutoRotation(float speed)
        : speed(speed)
    {
    }
};

} // namespace texplr
