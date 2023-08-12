#include <ecs/components/Transform.hpp>

namespace texplr {

const glm::vec3& Transform::getFront() const
{
    return m_front;
}

const glm::vec3& Transform::getUp() const
{
    return m_up;
}

const glm::vec3& Transform::getRight() const
{
    return m_right;
}

const glm::vec3& Transform::getWorldPosition() const
{
    return m_worldPosition;
}

const glm::mat4& Transform::getLocalMatrix() const
{
    return m_localMatrix;
}

const glm::mat4& Transform::getModelMatrix() const
{
    return m_modelMatrix;
}

} // namespace texplr
