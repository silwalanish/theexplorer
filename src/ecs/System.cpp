#include <ecs/System.hpp>

#include <ecs/World.hpp>

namespace texplr {

System::System()
{
}

System::~System()
{
}

void System::update(float deltaTime)
{
}

void System::registerEntity(EntityHandle handle)
{
    m_registeredEntities.insert(handle);
}

void System::unregisterEntity(EntityHandle handle)
{
    m_registeredEntities.erase(handle);
}

void System::registerWorld(World* world)
{
    m_world = world;
    m_eventBus = world->getEventBus();

    init();
}

} // namespace texplr
