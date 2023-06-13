#include <systems/EditorCameraController.hpp>

#include <core/Scene.hpp>

namespace texplr {

void EditorCameraController::OnUpdate(float deltaTime)
{

    for (EntityHandle entity : m_registeredEntities) {
        Camera& camera = m_world->getComponent<Camera>(entity);
        Transform& transform = m_world->getComponent<Transform>(entity);
        const EditorControls& contorls = m_world->getComponent<EditorControls>(entity);

        std::shared_ptr<Input> input = getInputManger();
        if (input->isKeyDown(KeyCodes::W)) {
            transform.position += transform.getFront() * contorls.moveSpeed * deltaTime;
        } else if (input->isKeyDown(KeyCodes::S)) {
            transform.position -= transform.getFront() * contorls.moveSpeed * deltaTime;
        }

        if (input->isKeyDown(KeyCodes::A)) {
            transform.position -= transform.getRight() * contorls.moveSpeed * deltaTime;
        } else if (input->isKeyDown(KeyCodes::D)) {
            transform.position += transform.getRight() * contorls.moveSpeed * deltaTime;
        }

        if (input->isMouseLocked()) {
            transform.rotation.x += input->getMousePositionOffset().y * deltaTime * contorls.mouseSensitivity;
            transform.rotation.y += input->getMousePositionOffset().x * deltaTime * contorls.mouseSensitivity;
        }
    }
}

} // namespace texplr
