#pragma once

#include <glm/glm.hpp>

#include <ecs/Component.hpp>

namespace texplr {

struct Transform : public Component<Transform> {
public:
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;

    Transform() = default;
    Transform(const Transform&) = default;

    Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
        : position(position)
        , rotation(rotation)
        , scale(scale) {};
};

} // namespace texplr
