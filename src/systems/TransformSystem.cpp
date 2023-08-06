#pragma once

#include <algorithm>
#include <queue>

#include <systems/TransformSystem.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace texplr {

void TransformSystem::OnInit()
{
    m_world->getEventBus()->subscribe(this, &TransformSystem::OnTransformAdded);
}

void TransformSystem::OnUpdate(float deltaTime)
{
    processTree(m_world->getSceneGraph()->getRoot(), Transform {});
}

void TransformSystem::OnTransformAdded(ComponentAddedEvent<Transform>* event)
{
    EntityHandle entity = event->entity;

    if (m_world->getSceneGraph()->isRoot(entity)) {
        processTree(entity, Transform {});
    } else {
        processTree(entity, m_world->getComponent<Transform>(m_world->getParent(entity)));
    }
}

void TransformSystem::processTree(EntityHandle root, const Transform& globalTransform)
{
    std::queue<EntityHandle> entites;
    entites.push(root);

    while (entites.size() > 0) {
        EntityHandle entity = entites.front();
        entites.pop();

        Transform& transform = m_world->getComponent<Transform>(entity);
        if (entity != root) {
            EntityHandle parent = m_world->getParent(entity);
            recalculateTransform(transform, m_world->getComponent<Transform>(parent));
        } else {
            recalculateTransform(transform, globalTransform);
        }

        for (EntityHandle child : m_world->getChildren(entity)) {
            entites.push(child);
        }
    }
}

void TransformSystem::calculateLocalMatrix(Transform& transform)
{
    transform.m_localMatrix = glm::mat4(1.0f);
    transform.m_localMatrix = glm::translate(transform.m_localMatrix, transform.position);
    transform.m_localMatrix = glm::rotate(transform.m_localMatrix, glm::radians(transform.rotation.x), glm::vec3(1.0, 0.0, 0.0));
    transform.m_localMatrix = glm::rotate(transform.m_localMatrix, glm::radians(transform.rotation.y), glm::vec3(0.0, 1.0, 0.0));
    transform.m_localMatrix = glm::rotate(transform.m_localMatrix, glm::radians(transform.rotation.z), glm::vec3(0.0, 0.0, 1.0));
    transform.m_localMatrix = glm::scale(transform.m_localMatrix, transform.scale);
}

void TransformSystem::calculateModelMatrix(Transform& transform, const Transform& parentTransform)
{
    transform.m_modelMatrix = parentTransform.getModelMatrix() * transform.getLocalMatrix();
}

void TransformSystem::calculateDirections(Transform& transform)
{
    transform.m_right = glm::normalize(glm::vec3(transform.m_modelMatrix[0][0], transform.m_modelMatrix[1][0], transform.m_modelMatrix[2][0]));
    transform.m_up = glm::normalize(glm::vec3(transform.m_modelMatrix[0][1], transform.m_modelMatrix[1][1], transform.m_modelMatrix[2][1]));
    transform.m_front = glm::normalize(glm::vec3(transform.m_modelMatrix[0][2], transform.m_modelMatrix[1][2], transform.m_modelMatrix[2][2]) * -1.0f);
}

void TransformSystem::recalculateTransform(Transform& transform, const Transform& parentTransform)
{
    calculateLocalMatrix(transform);
    calculateModelMatrix(transform, parentTransform);
    calculateDirections(transform);
}

} // namespace texplr
