#pragma once

#include <systems/TransformSystem.hpp>

namespace texplr {

void TransformSystem::OnInit() { }

void TransformSystem::OnUpdate(float deltaTime)
{
    for (EntityHandle entity : m_registeredEntities) {
        Transform& transform = m_world->getComponent<Transform>(entity);
        transform.recalculate();
    }
}

} // namespace texplr
