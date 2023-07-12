#include <game/ShowcaseScene.hpp>

#include <iostream>

#include <components/Camera.hpp>
#include <components/Mesh.hpp>
#include <components/NativeScript.hpp>
#include <components/Transform.hpp>
#include <ecs/Entity.hpp>
#include <systems/EditorCameraController.hpp>
#include <systems/Scripting.hpp>
#include <systems/TransformSystem.hpp>

#include <game/PlanetScript.hpp>

namespace texplr {

ShowcaseScene::ShowcaseScene(std::shared_ptr<EventBus> eventBus)
    : Scene(eventBus)
{
    m_eventBus->subscribe(this, &ShowcaseScene::OnMouseDown);
    m_eventBus->subscribe(this, &ShowcaseScene::OnMouseUp);
}

void ShowcaseScene::OnInit()
{
    m_world->registerSystem<TransformSystem>();
    m_world->registerSystem<EditorCameraController>();
    m_world->registerSystem<Scripting>();
    m_renderer = m_world->registerSystem<SceneRenderer>();

    Entity* camera = new Entity(m_world.get());
    camera->addComponent<Camera>(Camera { 0.01f, 100.0f, 60.0f, 1.33f, true });
    camera->addComponent<Transform>(Transform { glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 180.0f, 0.0f), glm::vec3(1.0f) });
    camera->addComponent<EditorControls>(EditorControls { 30.0f, 1.0f });
    setActiveCamera(camera->getHandle());

    Entity* planet = new Entity(m_world.get());
    planet->addComponent<Transform>(Transform { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(5.0f) });
    planet->addComponent<Mesh>(Mesh { MeshData { {
                                                     Vertex(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
                                                     Vertex(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
                                                     Vertex(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
                                                     Vertex(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),
                                                 },
                                          { 0, 1, 2, 0, 2, 3 } },
        Material { glm::vec3(1.0f, 1.0f, 0.0f) } });
    // planet->addScript(new PlanetScript());

    m_renderer->setScene(this);
}

void ShowcaseScene::OnUpdate(float deltaTime)
{
    m_renderer->render();
}

void ShowcaseScene::OnMouseDown(MouseButtonDownEvent* event)
{
    if (event->button == MouseButtons::BTN_LEFT) {
        getWindow()->lockMouse();
    }
}

void ShowcaseScene::OnMouseUp(MouseButtonUpEvent* event)
{
    if (event->button == MouseButtons::BTN_LEFT) {
        getWindow()->unlockMouse();
    }
}

} // namespace texplr
