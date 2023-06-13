#include <components/Transform.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace texplr {

void Transform::calculateModelMatrix()
{
    m_modelMatrix = glm::mat4(1.0f);
    m_modelMatrix = glm::translate(m_modelMatrix, position);
    m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
    m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
    m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));
    m_modelMatrix = glm::scale(m_modelMatrix, scale);
}

void Transform::calculateDirections()
{
    m_right = glm::normalize(glm::vec3(m_modelMatrix[0][0], m_modelMatrix[1][0], m_modelMatrix[2][0]));
    m_up = glm::normalize(glm::vec3(m_modelMatrix[0][1], m_modelMatrix[1][1], m_modelMatrix[2][1]));
    m_front = glm::normalize(glm::vec3(m_modelMatrix[0][2], m_modelMatrix[1][2], m_modelMatrix[2][2]));
}

void Transform::recalculate()
{
    calculateModelMatrix();
    calculateDirections();
}

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

const glm::mat4& Transform::getModelMatrix() const
{
    return m_modelMatrix;
}

} // namespace texplr
