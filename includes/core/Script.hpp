#pragma once

#include <ecs/EntityHandle.hpp>
#include <ecs/World.hpp>

namespace texplr {

class Script {
public:
    Script();
    ~Script();

    void init();
    void attach(EntityHandle entity, World* world);
    void update(float deltaTime);

    virtual void OnInit() = 0;
    virtual void OnAttach() = 0;
    virtual void OnUpdate(float deltaTime) = 0;

protected:
    EntityHandle m_entity;
    World* m_world = nullptr;
};

} // namespace texplr
