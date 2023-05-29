#include <systems/ActiveCameraFinder.hpp>

#include <iostream>

#include <core/Scene.hpp>
#include <ecs/Entity.hpp>
#include <ecs/World.hpp>

namespace texplr {

ActiveCameraFinder::ActiveCameraFinder()
{
}

ActiveCameraFinder::~ActiveCameraFinder()
{
}

void ActiveCameraFinder::onInit()
{
}

void ActiveCameraFinder::update(float deltaTime)
{
    Scene* scene = m_world->getScene();
    scene->setActiveCamera(0);

    for (auto entityHandle : m_registeredEntities) {
        Camera& cam = m_world->getComponent<Camera>(entityHandle);
        if (cam.isActive) {
            scene->setActiveCamera(entityHandle);
            break;
        }
    }

    if (scene->getActiveCamera() != 0) {
        Camera& cam = m_world->getComponent<Camera>(scene->getActiveCamera());
        std::cout << "Active Camera:: " << cam.near << ", " << cam.far << ", " << cam.fov << ", " << cam.aspectRatio << std::endl;
    }
}

} // namespace texplr
