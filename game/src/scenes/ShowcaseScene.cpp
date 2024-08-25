#include <game/scenes/ShowcaseScene.hpp>

#include <fstream>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <queue>

#include <core/Application.hpp>
#include <ecs/components/Camera.hpp>
#include <ecs/components/DirectionalLight.hpp>
#include <ecs/components/Mesh.hpp>
#include <ecs/components/Transform.hpp>
#include <game/scripts/EditorCameraController.hpp>
#include <scripting/ScriptableEntity.hpp>
#include <scripting/component/NativeScript.hpp>
#include <shapes/Cube.hpp>

namespace texplr {

ShowcaseScene::ShowcaseScene(std::shared_ptr<EventBus> eventBus)
    : RenderableScene(eventBus)
    , Scene(eventBus)
{
    m_eventBus->subscribe(this, &ShowcaseScene::OnMouseDown);
    m_eventBus->subscribe(this, &ShowcaseScene::OnMouseUp);
    m_eventBus->subscribe(this, &ShowcaseScene::OnKeyUp);
}

ShowcaseScene::~ShowcaseScene() { }

void ShowcaseScene::OnInit()
{
    std::shared_ptr<ScriptableWorld> world = createWorld<ScriptableWorld>();
    m_debugRenderer = world->registerSystem<DebugRenderer>();

    ScriptableEntity camera(world.get());
    camera.addComponent<Camera>(Camera { 0.01f, 1000.0f, 60.0f, 1.33f, true });
    camera.addComponent<Transform>(Transform { glm::vec3(0.0f, 2.0f, -5.0f), glm::vec3(20.0f, 190.0f, 0.0f), glm::vec3(1.0f) });
    camera.addScript<EditorCameraController>(30.0f, 5.0f);
    setActiveCamera(camera.getHandle());

    Entity sun(world.get());
    sun.addComponent<DirectionalLight>(DirectionalLight { Light { 0.05f, glm::vec3(0.8f, 0.8f, 0.9f), glm::vec3(0.0f, -0.25f, 0.5f) } });
    setSun(sun.getHandle());

    Entity cube(world.get());
    cube.addComponent<Transform>(Transform {});
    cube.addComponent<Mesh>(Mesh { Cube::Generate(1.0f), Material { glm::vec4(1.0f) } });

    Entity cube2(world.get());
    cube2.addComponent<Transform>(Transform { glm::vec3(2.0f), glm::vec3(20.0f), glm::vec3(1.0f) });
    cube2.addComponent<Mesh>(Mesh { Cube::Generate(2.0f), Material { glm::vec4(1.0f, 1.0f, 0.0f, 1.0f) } });

    Entity ground(world.get());
    ground.addComponent<Transform>(Transform { glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(20.0f, 1.0f, 20.0f) });
    ground.addComponent<Mesh>(Mesh { Cube::Generate(1.0f), Material { glm::vec4(0.5f, 1.0f, 0.5f, 1.0f) } });

    m_renderer->setScene(this);
    m_debugRenderer->setScene(this);
}

void ShowcaseScene::OnUpdate(float deltaTime)
{
    RenderableScene::OnUpdate(deltaTime);

    if (m_debugRender) {
        m_debugRenderer->render();
    }
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

void ShowcaseScene::OnKeyUp(KeyUpEvent* event)
{
    if (event->key == KeyCodes::GRAVE_ACCENT) {
        m_debugRender = !m_debugRender;
    }
}

} // namespace texplr
