#pragma once

#include <ecs/Component.hpp>

namespace texplr {

struct Transform : public Component<Transform> {
public:
    float x;
    float y;
    float z;

    Transform() = default;
    Transform(const Transform&) = default;

    Transform(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z) {};
};

} // namespace texplr
