#include <ecs/World.hpp>

#include <components/NativeScript.hpp>
#include <core/Scene.hpp>
#include <scripting/Script.hpp>

namespace texplr {

World::World(std::shared_ptr<EventBus> eventBus)
    : m_eventBus(eventBus)
{
    m_entityManager = std::make_unique<EntityManager>(m_eventBus);
}

World::~World()
{
}

void World::update(float deltaTime)
{
    for (auto& system : m_systems) {
        system->update(deltaTime);
    }
}

EntityHandle World::createEntity()
{
    return m_entityManager->createEntity();
}

void World::destroyEntity(EntityHandle handle)
{
    m_entityManager->destroyEntity(handle);
}

void World::addScript(EntityHandle handle, Script* script)
{
    if (!hasComponent<NativeScript>(handle)) {
        addComponent<NativeScript>(handle, NativeScript {});
    }

    script->init();
    script->attach(handle, this);

    getComponent<NativeScript>(handle).scripts.push_back(script);
}

void World::registerToScene(Scene* scene)
{
    m_scene = scene;
}

Scene* World::getScene()
{
    return m_scene;
}

const Scene* World::getScene() const
{
    return m_scene;
}

std::shared_ptr<EventBus> World::getEventBus() const
{
    return m_eventBus;
}

} // namespace texplr
