#pragma once

#include <ecs/Component.hpp>

namespace texplr {

struct Camera : public Component<Camera> {
public:
    float near;
    float far;
    float fov;
    float aspectRatio;
    bool isActive;

    Camera() = default;
    Camera(const Camera& cam) = default;

    Camera(float near, float far, float fov, float aspectRatio, bool isActive)
        : near(near)
        , far(far)
        , fov(fov)
        , aspectRatio(aspectRatio)
        , isActive(isActive) {};
};

} // namespace texplr
