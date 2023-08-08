#include <scripting/NativeScriptEngine.hpp>

namespace texplr {

void NativeScriptEngine::OnInit()
{
}

void NativeScriptEngine::OnUpdate(float deltaTime)
{
    for (EntityHandle entity : m_registeredEntities) {
        NativeScript& scripts = m_world->getComponent<NativeScript>(entity);

        for (std::shared_ptr<Script> script : scripts.scripts) {
            script->update(deltaTime);
        }
    }
}

} // namespace texplr
