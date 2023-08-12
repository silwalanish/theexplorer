#include <game/ShowcaseScene.hpp>

#include <fstream>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <queue>

#include <core/Application.hpp>
#include <ecs/components/Camera.hpp>
#include <ecs/components/DirectionalLight.hpp>
#include <ecs/components/Mesh.hpp>
#include <ecs/components/Transform.hpp>
#include <scripting/ScriptableEntity.hpp>
#include <scripting/component/NativeScript.hpp>
#include <scripts/EditorCameraController.hpp>
#include <scripts/TerrainGenerator.hpp>

namespace texplr {

ShowcaseScene::ShowcaseScene(std::shared_ptr<EventBus> eventBus)
    : Scene(eventBus)
{
    m_world = std::make_shared<ScriptableWorld>(m_eventBus);
    m_world->registerToScene(this);

    m_eventBus->subscribe(this, &ShowcaseScene::OnMouseDown);
    m_eventBus->subscribe(this, &ShowcaseScene::OnMouseUp);
    m_eventBus->subscribe(this, &ShowcaseScene::OnKeyUp);
}

void ShowcaseScene::OnInit()
{
    m_renderer = m_world->registerSystem<SceneRenderer>();
    m_debugRenderer = m_world->registerSystem<DebugRenderer>();

    ScriptableEntity camera(m_world.get());
    camera.addComponent<Camera>(Camera { 0.01f, 1000.0f, 60.0f, 1.33f, true });
    camera.addComponent<Transform>(Transform { glm::vec3(0.0f, 50.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f) });
    camera.addScript<EditorCameraController>(30.0f, 1.0f);
    setActiveCamera(camera.getHandle());

    HeightMap heightMap(0.01f, 15.0f, 4.0f, 0.1f);
    float chunkSize = 10.0f;
    int chunkPerRow = 5;
    glm::vec3 startChunk(-(chunkPerRow - 1) * (chunkSize / 2.0f), 0.0f, -(chunkPerRow - 1) * (chunkSize / 2.0f));

    Entity terrain(m_world.get());
    terrain.addComponent<Transform>(Transform { startChunk, glm::vec3(0.0f), glm::vec3(1.0f) });

    for (int i = 0; i < chunkPerRow; i++) {
        for (int j = 0; j < chunkPerRow; j++) {
            ScriptableEntity terrainChunk(m_world.get());
            terrainChunk.addComponent<Transform>(Transform { glm::vec3(i * chunkSize, 0.0f, j * chunkSize), glm::vec3(0.0f), glm::vec3(1.0f) });
            terrainChunk.addScript<TerrainGenerator>(25, chunkSize, heightMap);

            terrain.addChild(terrainChunk.getHandle());
        }
    }

    Entity sun(m_world.get());
    sun.addComponent<DirectionalLight>(DirectionalLight { Light { 0.05f, glm::vec3(0.8f, 0.8f, 0.9f), glm::vec3(0.0f, -0.25f, 0.5f) } });
    setSun(sun.getHandle());

    m_renderer->setScene(this);
    m_debugRenderer->setScene(this);
}

void ShowcaseScene::OnUpdate(float deltaTime)
{
    m_world->update(deltaTime);
    m_renderer->render();

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

EntityHandle ShowcaseScene::getSun() const
{
    return m_sun;
}

EntityHandle ShowcaseScene::getActiveCamera() const
{
    return m_activeCamera;
}

std::shared_ptr<ScriptableWorld> ShowcaseScene::getWorld() const
{
    return m_world;
}

void ShowcaseScene::setSun(EntityHandle sun)
{
    assert(m_world->hasComponent<DirectionalLight>(sun) && "Entity needs to have 'DirectionalLight' component.");

    m_sun = sun;
}

void ShowcaseScene::setActiveCamera(EntityHandle camera)
{
    assert(m_world->hasComponent<Camera>(camera) && "Entity needs to have 'Camera' component.");

    m_activeCamera = camera;
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
