#include <scripts/EditorCameraController.hpp>

#include <core/Scene.hpp>
#include <ecs/components/Camera.hpp>
#include <ecs/components/Transform.hpp>

namespace texplr {

EditorCameraController::EditorCameraController(float mouseSensitivity, float moveSpeed)
    : m_mouseSensitivity(mouseSensitivity)
    , m_moveSpeed(moveSpeed)
{
}

void EditorCameraController::OnInit()
{
}

void EditorCameraController::OnAttach()
{
}

void EditorCameraController::OnUpdate(float deltaTime)
{
    Camera& camera = m_world->getComponent<Camera>(m_entity);
    Transform& transform = m_world->getComponent<Transform>(m_entity);

    std::shared_ptr<Input> input = getInputManger();
    if (input->isKeyDown(KeyCodes::W)) {
        transform.position += transform.getFront() * m_moveSpeed * deltaTime;
    } else if (input->isKeyDown(KeyCodes::S)) {
        transform.position -= transform.getFront() * m_moveSpeed * deltaTime;
    }

    if (input->isKeyDown(KeyCodes::A)) {
        transform.position -= transform.getRight() * m_moveSpeed * deltaTime;
    } else if (input->isKeyDown(KeyCodes::D)) {
        transform.position += transform.getRight() * m_moveSpeed * deltaTime;
    }

    if (input->isMouseLocked()) {
        transform.rotation.x += input->getMousePositionOffset().y * deltaTime * m_mouseSensitivity;
        transform.rotation.y += input->getMousePositionOffset().x * deltaTime * m_mouseSensitivity;
    }
}

} // namespace texplr
