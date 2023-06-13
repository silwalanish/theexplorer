#pragma once

#include <systems/Rotator.hpp>

namespace texplr {

void Rotator::OnInit() { }

void Rotator::OnUpdate(float deltaTime)
{
    for (EntityHandle entity : m_registeredEntities) {
        Transform& transform = m_world->getComponent<Transform>(entity);
        const AutoRotation& rotation = m_world->getComponent<AutoRotation>(entity);

        transform.rotation.y += rotation.speed * deltaTime;
        transform.position += transform.getFront() * 1.0f * deltaTime;
    }
}

} // namespace texplr
