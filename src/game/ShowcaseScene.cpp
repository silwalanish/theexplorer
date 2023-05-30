#include <game/ShowcaseScene.hpp>

#include <iostream>

#include <components/Camera.hpp>
#include <components/Mesh.hpp>
#include <components/Transform.hpp>
#include <ecs/Entity.hpp>

namespace texplr {

ShowcaseScene::ShowcaseScene(std::shared_ptr<EventBus> eventBus)
    : Scene(eventBus)
{
}

void ShowcaseScene::OnInit()
{
    m_renderer = m_world->registerSystem<SceneRenderer>();

    Entity* camera = new Entity(m_world.get());
    camera->addComponent<Camera>(Camera { 0.01f, 100.0f, 45.0f, 1.33f, true });
    camera->addComponent<Transform>(Transform { glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f) });

    Entity* bottomTri = new Entity(m_world.get());
    bottomTri->addComponent<Transform>(Transform { glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f) });
    bottomTri->addComponent<Mesh>(Mesh {
        { Vertex { glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f) },
            Vertex { glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f) },
            Vertex { glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f) } },
        { 0, 1, 2 },
        Material { glm::vec3(1.0f, 0.0f, 0.0f) } });

    Entity* topTri = new Entity(m_world.get());
    topTri->addComponent<Transform>(Transform { glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f) });
    topTri->addComponent<Mesh>(Mesh {
        { Vertex { glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f) },
            Vertex { glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f) },
            Vertex { glm::vec3(0.0f, -0.1f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f) } },
        { 0, 1, 2 },
        Material { glm::vec3(0.0f, 0.0f, 1.0f) } });

    m_renderer->setScene(this);
}

void ShowcaseScene::OnUpdate(float deltaTime)
{
    m_renderer->render();
}

} // namespace texplr
