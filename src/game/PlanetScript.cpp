#include <game/PlanetScript.hpp>

#include <components/Transform.hpp>

namespace texplr {

void PlanetScript::OnInit() { }

void PlanetScript::OnAttach() { }

void PlanetScript::OnUpdate(float deltaTime)
{
    Transform& transform = m_world->getComponent<Transform>(m_entity);
    transform.rotation.y += 20.0f * deltaTime;
}

} // namespace texplr
