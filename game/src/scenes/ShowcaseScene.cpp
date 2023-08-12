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
#include <game/scripts/TerrainGenerator.hpp>
#include <scripting/ScriptableEntity.hpp>
#include <scripting/component/NativeScript.hpp>

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
    camera.addComponent<Transform>(Transform { glm::vec3(0.0f, 50.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f) });
    camera.addScript<EditorCameraController>(30.0f, 1.0f);
    setActiveCamera(camera.getHandle());

    HeightMap heightMap(0.01f, 15.0f, 4.0f, 0.1f);
    float chunkSize = 10.0f;
    int chunkPerRow = 5;
    glm::vec3 startChunk(-(chunkPerRow - 1) * (chunkSize / 2.0f), 0.0f, -(chunkPerRow - 1) * (chunkSize / 2.0f));

    Entity terrain(world.get());
    terrain.addComponent<Transform>(Transform { startChunk, glm::vec3(0.0f), glm::vec3(1.0f) });

    for (int i = 0; i < chunkPerRow; i++) {
        for (int j = 0; j < chunkPerRow; j++) {
            ScriptableEntity terrainChunk(world.get());
            terrainChunk.addComponent<Transform>(Transform { glm::vec3(i * chunkSize, 0.0f, j * chunkSize), glm::vec3(0.0f), glm::vec3(1.0f) });
            terrainChunk.addScript<TerrainGenerator>(25, chunkSize, heightMap);

            terrain.addChild(terrainChunk.getHandle());
        }
    }

    Entity sun(world.get());
    sun.addComponent<DirectionalLight>(DirectionalLight { Light { 0.05f, glm::vec3(0.8f, 0.8f, 0.9f), glm::vec3(0.0f, -0.25f, 0.5f) } });
    setSun(sun.getHandle());

    m_renderer->setScene(this);
    m_debugRenderer->setScene(this);
}

void ShowcaseScene::OnUpdate(float deltaTime)
{
    RenderableScene::OnUpdate(deltaTime);

    if (m_debugRender) {
        m_debugRenderer->render();
    }

    // std::ofstream file("debug.log");
    // std::queue<EntityHandle> entites;
    // entites.push(m_world->getSceneGraph()->getRoot());

    // while (entites.size() > 0) {
    //     EntityHandle entity = entites.front();
    //     entites.pop();

    //     Transform& transform = m_world->getComponent<Transform>(entity);
    //     if (m_world->getSceneGraph()->isRoot(entity)) {
    //         file << "ID: " << entity << std::endl
    //              << "\tPOSITION: " << glm::to_string(transform.position) << std::endl
    //              << "\tROTATION: " << glm::to_string(transform.rotation) << std::endl
    //              << "\tSCALE: " << glm::to_string(transform.scale) << std::endl
    //              << "\tLOCAL MATRIX: " << glm::to_string(transform.getLocalMatrix()) << std::endl
    //              << "\tMODEL MATRIX: " << glm::to_string(transform.getModelMatrix()) << std::endl
    //              << "\tPARENT ID: ---ROOT---" << std::endl;
    //     } else {
    //         EntityHandle parent = m_world->getParent(entity);
    //         Transform& parentTransform = m_world->getComponent<Transform>(parent);

    //         file << "ID: " << entity << std::endl
    //              << "\tPOSITION: " << glm::to_string(transform.position) << std::endl
    //              << "\tROTATION: " << glm::to_string(transform.rotation) << std::endl
    //              << "\tSCALE: " << glm::to_string(transform.scale) << std::endl
    //              << "\tLOCAL MATRIX: " << glm::to_string(transform.getLocalMatrix()) << std::endl
    //              << "\tMODEL MATRIX: " << glm::to_string(transform.getModelMatrix()) << std::endl
    //              << "\tPARENT ID: " << parent << std::endl
    //              << "\tPARENT MODEL MATRIX: " << glm::to_string(parentTransform.getModelMatrix()) << std::endl;
    //     }

    //         for (EntityHandle child : m_world->getChildren(entity)) {
    //             entites.push(child);
    //         }
    // // }

    // file.close();

    // m_application->stop();
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
