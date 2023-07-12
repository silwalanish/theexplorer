#include <scripting/Script.hpp>

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

} // namespace texplr
