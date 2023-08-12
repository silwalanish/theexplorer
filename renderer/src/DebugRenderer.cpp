#include <renderer/DebugRenderer.hpp>

#include <core/utils/Math.hpp>
#include <ecs/components/Camera.hpp>
#include <ecs/components/DirectionalLight.hpp>
#include <renderer/RenderableScene.hpp>
#include <renderer/shaders/DebugShader.hpp>

namespace texplr {

void DebugRenderer::OnInit()
{
    m_shader = std::make_shared<DebugShader>();
}

void DebugRenderer::OnUpdate(float deltaTime)
{
    const Camera& camera = m_scene->getWorld()->getComponent<Camera>(m_scene->getActiveCamera());
    const Transform& cameraTransform = m_scene->getWorld()->getComponent<Transform>(m_scene->getActiveCamera());

    m_projectionMatrix = Math::calculateProjectionMatrix(camera);
    m_viewMatrix = Math::calculateViewMatrix(cameraTransform);

    for (EntityHandle entity : m_registeredEntities) {
        const Transform& transform = m_world->getComponent<Transform>(entity);

        MeshData meshData = MeshData {
            {
                Vertex { transform.getWorldPosition(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f) },
                Vertex { transform.getWorldPosition() + transform.getRight(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f) },
                Vertex { transform.getWorldPosition(), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f) },
                Vertex { transform.getWorldPosition() + transform.getUp(), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f) },
                Vertex { transform.getWorldPosition(), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f) },
                Vertex { transform.getWorldPosition() + transform.getFront(), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f) },
            },
            { 0, 1, 2, 3, 4, 5 }
        };

        std::shared_ptr<VertexArray> vao = std::make_shared<VertexArray>(MeshPrimitive::LINES);
        vao->loadMeshData(meshData);

        m_vaos[entity] = vao;
    }
}

void DebugRenderer::begin()
{
    glDisable(GL_DEPTH_TEST);
    m_shader->use();
}

void DebugRenderer::render()
{
    begin();

    m_shader->loadProjectionMatrix(m_projectionMatrix);
    m_shader->loadViewMatrix(m_viewMatrix);

    for (EntityHandle entity : m_registeredEntities) {
        if (entity == m_scene->getActiveCamera()) {
            continue;
        }

        const Transform& transform = m_world->getComponent<Transform>(entity);
        m_shader->loadModelMatrix(glm::mat4(1.0f));

        std::shared_ptr<VertexArray> vao = m_vaos[entity];
        vao->draw();
    }
}

void DebugRenderer::setScene(RenderableScene* scene)
{
    m_scene = scene;
}

RenderableScene* DebugRenderer::getScene()
{
    return m_scene;
}

const RenderableScene* DebugRenderer::getScene() const
{
    return m_scene;
}

} // namespace texplr
