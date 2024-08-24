#include <renderer/RenderableScene.hpp>

#include <ecs/components/Camera.hpp>
#include <ecs/components/DirectionalLight.hpp>

namespace texplr {

RenderableScene::RenderableScene(std::shared_ptr<EventBus> eventBus)
    : Scene(eventBus)
{
}

RenderableScene::~RenderableScene() { }

void RenderableScene::OnUpdate(float deltaTime)
{
    if (m_world) {
        m_world->update(deltaTime);
        m_renderer->render();
    }
}

EntityHandle RenderableScene::getSun() const
{
    return m_sun;
}

EntityHandle RenderableScene::getActiveCamera() const
{
    return m_activeCamera;
}

std::shared_ptr<World> RenderableScene::getWorld() const
{
    return m_world;
}

void RenderableScene::setSun(EntityHandle sun)
{
    assert(m_world->hasComponent<DirectionalLight>(sun) && "Scene needs to have 'DirectionalLight' component.");

    m_sun = sun;
}

void RenderableScene::setActiveCamera(EntityHandle camera)
{
    assert(m_world->hasComponent<Camera>(camera) && "Scene needs to have 'Camera' component.");

    m_activeCamera = camera;
}

} // namespace texplr
