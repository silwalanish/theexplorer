#include <game/ShowcaseScene.hpp>

#include <iostream>

#include <components/Camera.hpp>
#include <components/Transform.hpp>
#include <ecs/Entity.hpp>
#include <systems/ActiveCameraFinder.hpp>

namespace texplr {

ShowcaseScene::ShowcaseScene(std::shared_ptr<EventBus> eventBus)
    : Scene(eventBus)
{
}

void ShowcaseScene::OnInit()
{
    m_world->registerSystem<ActiveCameraFinder>();

    Entity* camera = new Entity(m_world.get());
    camera->addComponent<Camera>(Camera { 0.01f, 100.0f, 45.0f, 1.33f, true });

    Entity* activeCamera = new Entity(m_world.get());
    activeCamera->addComponent<Camera>(Camera { 0.01f, 100.0f, 90.0f, 1.33f, true });
    activeCamera->addComponent<Transform>(Transform { 1.0f, 0.0f, 1.0f });

    std::cout << "Camera has both (Camera and Transform):: " << m_world->hasAllComponent<Transform, Camera>(camera->getHandle()) << std::endl;
    std::cout << "Active Camera has both (Camera and Transform):: " << m_world->hasAllComponent<Transform, Camera>(activeCamera->getHandle()) << std::endl;

    Entity* player = new Entity(m_world.get());
    Entity* enemy = new Entity(m_world.get());
}

void ShowcaseScene::OnUpdate(float deltaTime)
{
}

} // namespace texplr
