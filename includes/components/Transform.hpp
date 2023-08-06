#pragma once

#include <glm/glm.hpp>

#include <ecs/Component.hpp>

namespace texplr {

struct Transform : public Component<Transform> {
public:
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec3 rotation = glm::vec3(0.0f);

    Transform() = default;
    Transform(const Transform&) = default;

    Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
        : position(position)
        , rotation(rotation)
        , scale(scale) {};

    const glm::vec3& getFront() const;
    const glm::vec3& getUp() const;
    const glm::vec3& getRight() const;

    const glm::vec3& getWorldPosition() const;

    const glm::mat4& getLocalMatrix() const;
    const glm::mat4& getModelMatrix() const;

private:
    glm::vec3 m_front = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_right = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 m_worldPosition = glm::vec3(0.0f);
    glm::mat4 m_localMatrix = glm::mat4(1.0f);
    glm::mat4 m_modelMatrix = glm::mat4(1.0f);

    friend class TransformSystem;
};

} // namespace texplr
