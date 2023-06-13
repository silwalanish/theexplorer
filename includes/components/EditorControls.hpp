#pragma once

#include <ecs/Component.hpp>

namespace texplr {

struct EditorControls : public Component<EditorControls> {
public:
    float mouseSensitivity;
    float moveSpeed;

    EditorControls() = default;
    EditorControls(const EditorControls& cam) = default;

    EditorControls(float mouseSensitivity, float moveSpeed)
        : mouseSensitivity(mouseSensitivity)
        , moveSpeed(moveSpeed)
    {
    }
};

} // namespace texplr
