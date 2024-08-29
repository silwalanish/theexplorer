#include <game/scenes/ShowcaseScene.hpp>

#include <fstream>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <queue>

#include <core/Application.hpp>
#include <ecs/components/Camera.hpp>
#include <ecs/components/DirectionalLight.hpp>
#include <ecs/components/Mesh.hpp>
#include <ecs/components/Transform.hpp>
#include <game/scripts/EditorCameraController.hpp>
#include <scripting/ScriptableEntity.hpp>
#include <scripting/component/NativeScript.hpp>
#include <shapes/Cube.hpp>

#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>

namespace texplr {

ShowcaseScene::ShowcaseScene(std::shared_ptr<EventBus> eventBus)
    : RenderableScene(eventBus)
    , Scene(eventBus)
{
    m_eventBus->subscribe(this, &ShowcaseScene::OnMouseDown);
    m_eventBus->subscribe(this, &ShowcaseScene::OnMouseUp);
    m_eventBus->subscribe(this, &ShowcaseScene::OnKeyUp);
}

ShowcaseScene::~ShowcaseScene() { }

void ShowcaseScene::OnInit()
{
    m_collisionConfiguration = std::make_shared<btDefaultCollisionConfiguration>();
    m_dispatcher = std::make_shared<btCollisionDispatcher>(m_collisionConfiguration.get());
    m_broadphase = std::make_shared<btDbvtBroadphase>();
    m_solver = std::make_shared<btSequentialImpulseConstraintSolver>();
    m_dynamicsWorld = std::make_shared<btDiscreteDynamicsWorld>(m_dispatcher.get(), m_broadphase.get(), m_solver.get(), m_collisionConfiguration.get());
    m_dynamicsWorld->setGravity(btVector3(0, -10, 0));

    std::shared_ptr<ScriptableWorld> world = createWorld<ScriptableWorld>();
    m_debugRenderer = world->registerSystem<DebugRenderer>();

    ScriptableEntity camera(world.get());
    camera.addComponent<Camera>(Camera { 0.01f, 1000.0f, 60.0f, 1.33f, true });
    camera.addComponent<Transform>(Transform { glm::vec3(0.0f, 2.0f, -10.0f), glm::vec3(20.0f, 190.0f, 0.0f), glm::vec3(1.0f) });
    camera.addScript<EditorCameraController>(30.0f, 5.0f);
    setActiveCamera(camera.getHandle());

    Entity sun(world.get());
    sun.addComponent<DirectionalLight>(DirectionalLight { Light { 0.05f, glm::vec3(0.8f, 0.8f, 0.9f), glm::vec3(0.0f, -0.25f, 0.5f) } });
    setSun(sun.getHandle());

    Entity cube(world.get());
    cube.addComponent<Transform>(Transform { glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f) });
    cube.addComponent<Mesh>(Mesh { Cube::Generate(1.0f), Material { glm::vec4(1.0f) } });
    addRigidBody(cube, 0.5f, new btBoxShape(btVector3(0.5f, 0.5f, 0.5f)));

    Entity cube2(world.get());
    cube2.addComponent<Transform>(Transform { glm::vec3(1.0f, 5.0f, 0.0f), glm::vec3(20.0f), glm::vec3(1.0f) });
    cube2.addComponent<Mesh>(Mesh { Cube::Generate(2.0f), Material { glm::vec4(1.0f, 1.0f, 0.0f, 1.0f) } });
    addRigidBody(cube2, 0.5f, new btBoxShape(btVector3(1.0f, 1.0f, 1.0f)));

    Entity ground(world.get());
    ground.addComponent<Transform>(Transform { glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(20.0f, 1.0f, 20.0f) });
    ground.addComponent<Mesh>(Mesh { Cube::Generate(1.0f), Material { glm::vec4(0.5f, 1.0f, 0.5f, 1.0f) } });
    addRigidBody(ground, 0.0f, new btBoxShape(btVector3(10.0f, 0.5f, 10.0f)));

    m_renderer->setScene(this);
    m_debugRenderer->setScene(this);
}

void ShowcaseScene::addRigidBody(Entity entity, float mass, btCollisionShape* shape)
{
    bool isDynamic = (mass != 0.f);
    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        shape->calculateLocalInertia(mass, localInertia);

    const Transform& transform = entity.getComponent<Transform>();
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 position;
    glm::vec3 skew;
    glm::vec4 prespective;
    glm::decompose(transform.getModelMatrix(), scale, rotation, position, skew, prespective);

    const btTransform startTransform = btTransform(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w), btVector3(position.x, position.y, position.z));

    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, shape, localInertia);
    btRigidBody* body = new btRigidBody(cInfo);
    body->setUserIndex(entity.getHandle());
    m_dynamicsWorld->addRigidBody(body);
}

void ShowcaseScene::OnUpdate(float deltaTime)
{
    m_dynamicsWorld->stepSimulation(deltaTime);

    int numCollisionObjects = m_dynamicsWorld->getNumCollisionObjects();
    for (int i = 0; i < numCollisionObjects; ++i) {
        btCollisionObject* collisionObject = m_dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody* rigidBody = btRigidBody::upcast(collisionObject);

        if (rigidBody) {
            btTransform transform = rigidBody->getWorldTransform();
            btVector3 position = transform.getOrigin();
            btQuaternion q = transform.getRotation();

            Entity entity(rigidBody->getUserIndex(), m_world.get());
            Transform& entityTransform = entity.getComponent<Transform>();
            entityTransform.position = glm::vec3(position.x(), position.y(), position.z());
            entityTransform.rotation.x = glm::degrees(atan2(2.0f * (q.y() * q.z() + q.w() * q.x()), 1.0f - 2.0f * (q.x() * q.x() + q.y() * q.y())));
            entityTransform.rotation.y = glm::degrees(asin(2.0f * (q.w() * q.y() - q.x() * q.z())));
            entityTransform.rotation.z = glm::degrees(atan2(2.0f * (q.x() * q.y() + q.w() * q.z()), 1.0f - 2.0f * (q.y() * q.y() + q.z() * q.z())));
        }
    }

    RenderableScene::OnUpdate(deltaTime);

    if (m_debugRender) {
        m_debugRenderer->render();
    }
}
void ShowcaseScene::OnMouseDown(MouseButtonDownEvent* event)
{
    if (event->button == MouseButtons::BTN_LEFT) {
        getWindow()->lockMouse();
    }
}

void ShowcaseScene::OnMouseUp(MouseButtonUpEvent* event)
{
    if (event->button == MouseButtons::BTN_LEFT) {
        getWindow()->unlockMouse();
    }
}

void ShowcaseScene::OnKeyUp(KeyUpEvent* event)
{
    if (event->key == KeyCodes::GRAVE_ACCENT) {
        m_debugRender = !m_debugRender;
    }
}

} // namespace texplr
