#pragma once

#include <ecs/Entity.hpp>
#include <scripting/ScriptableWorld.hpp>

namespace texplr {

class ScriptableEntity : public virtual Entity {
public:
    ScriptableEntity(ScriptableWorld* world);
    ScriptableEntity(EntityHandle handle, ScriptableWorld* world);
    ScriptableEntity(const ScriptableEntity& entity);

    template <typename ScriptType, typename... Args>
    void addScript(const Args&... args)
    {
        dynamic_cast<ScriptableWorld*>(m_world)->addScript<ScriptType, Args...>(m_handle, args...);
    }
};

} // namespace texplr
