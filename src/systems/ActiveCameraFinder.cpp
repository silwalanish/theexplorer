#include <systems/ActiveCameraFinder.hpp>

#include <iostream>

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
    m_world->setActiveCamera(0);

    for (auto entityHandle : m_registeredEntities) {
        Camera& cam = m_world->getComponent<Camera>(entityHandle);
        if (cam.isActive) {
            m_world->setActiveCamera(entityHandle);
            break;
        }
    }

    if (m_world->getActiveCamera() != 0) {
        Camera& cam = m_world->getComponent<Camera>(m_world->getActiveCamera());
        std::cout << "Active Camera:: " << cam.near << ", " << cam.far << ", " << cam.fov << ", " << cam.aspectRatio << std::endl;
    }
}

} // namespace texplr
