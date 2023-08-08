#include <scripting/Script.hpp>

#include <core/Scene.hpp>

namespace texplr {

Script::Script() { }

Script::~Script() { }

void Script::init()
{
    OnInit();
}

void Script::attach(EntityHandle entity, World* world)
{
    m_entity = entity;
    m_world = world;
    OnAttach();
}

void Script::update(float deltaTime)
{
    OnUpdate(deltaTime);
}

std::shared_ptr<Input> Script::getInputManger()
{
    return m_world->getScene()->getInputManager();
}

} // namespace texplr
