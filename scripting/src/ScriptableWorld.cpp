#include <scripting/ScriptableWorld.hpp>

#include <scripting/NativeScriptEngine.hpp>
#include <scripting/component/NativeScript.hpp>

namespace texplr {

ScriptableWorld::ScriptableWorld(std::shared_ptr<EventBus> eventBus)
    : World(eventBus)
{
    registerSystem<NativeScriptEngine>();
}

ScriptableWorld::~ScriptableWorld() { }

} // namespace texplr
