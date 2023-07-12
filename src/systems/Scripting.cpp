#include <systems/Scripting.hpp>

namespace texplr {

void Scripting::OnInit()
{
}

void Scripting::OnUpdate(float deltaTime)
{
    for (EntityHandle entity : m_registeredEntities) {
        NativeScript& scripts = m_world->getComponent<NativeScript>(entity);

        for (Script* script : scripts.scripts) {
            script->update(deltaTime);
        }
    }
}

} // namespace texplr
