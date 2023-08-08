#include <scripting/ScriptableEntity.hpp>

namespace texplr {

ScriptableEntity::ScriptableEntity(ScriptableWorld* world)
    : Entity(world)
{
}

ScriptableEntity::ScriptableEntity(EntityHandle handle, ScriptableWorld* world)
    : Entity(handle, world)
{
}

ScriptableEntity::ScriptableEntity(const ScriptableEntity& entity)
    : Entity(entity)
{
}

} // namespace texplr
