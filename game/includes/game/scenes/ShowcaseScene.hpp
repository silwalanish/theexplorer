#pragma once

#include <renderer/DebugRenderer.hpp>
#include <renderer/RenderableScene.hpp>
#include <ecs/Entity.hpp>

#include <btBulletDynamicsCommon.h>

namespace texplr {

class ShowcaseScene : public virtual RenderableScene {
public:
    ShowcaseScene(std::shared_ptr<EventBus> eventBus);
    virtual ~ShowcaseScene();

    virtual void OnInit() override;
    virtual void OnUpdate(float deltaTime) override;

private:
    bool m_debugRender = false;
    std::shared_ptr<DebugRenderer> m_debugRenderer;

    std::shared_ptr<btBroadphaseInterface> m_broadphase;
    std::shared_ptr<btCollisionDispatcher> m_dispatcher;
    std::shared_ptr<btConstraintSolver> m_solver;
    std::shared_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;
    std::shared_ptr<btDiscreteDynamicsWorld> m_dynamicsWorld;

    void addRigidBody(Entity entity, float mass, btCollisionShape* shape);

    void OnMouseDown(MouseButtonDownEvent* event);
    void OnMouseUp(MouseButtonUpEvent* event);
    void OnKeyUp(KeyUpEvent* event);
};

} // namespace texplr
