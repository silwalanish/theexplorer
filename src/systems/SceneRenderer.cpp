#include <systems/SceneRenderer.hpp>

#include <ecs/components/Camera.hpp>
#include <ecs/components/DirectionalLight.hpp>
#include <game/ShowcaseScene.hpp>
#include <shaders/BasicShader.hpp>
#include <utils/Math.hpp>

namespace texplr {

void SceneRenderer::OnInit()
{
    m_shader = std::make_shared<BasicShader>();
}

void SceneRenderer::OnUpdate(float deltaTime)
{
    const Camera& camera = m_scene->getWorld()->getComponent<Camera>(m_scene->getActiveCamera());
    const Transform& cameraTransform = m_scene->getWorld()->getComponent<Transform>(m_scene->getActiveCamera());

    m_projectionMatrix = Math::calculateProjectionMatrix(camera);
    m_viewMatrix = Math::calculateViewMatrix(cameraTransform);

    for (EntityHandle entity : m_registeredEntities) {
        if (m_vaos.find(entity) != m_vaos.end()) {
            continue;
        }

        const Mesh& mesh = m_world->getComponent<Mesh>(entity);
        std::shared_ptr<VertexArray> vao = std::make_shared<VertexArray>(MeshPrimitive::TRIANGLES);
        vao->loadMeshData(mesh.meshData);

        m_vaos[entity] = vao;
    }
}

void SceneRenderer::begin()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    m_shader->use();
}

void SceneRenderer::render()
{
    const DirectionalLight& sun = m_scene->getWorld()->getComponent<DirectionalLight>(m_scene->getSun());

    begin();

    m_shader->loadProjectionMatrix(m_projectionMatrix);
    m_shader->loadViewMatrix(m_viewMatrix);
    m_shader->loadSun(sun.light);

    for (EntityHandle entity : m_registeredEntities) {
        const Transform& transform = m_world->getComponent<Transform>(entity);

        glm::mat4 modelMatrix = transform.getModelMatrix();
        m_shader->loadModelMatrix(modelMatrix);
        m_shader->loadNormalMatrix(glm::mat3(glm::transpose(glm::inverse(modelMatrix))));

        const Mesh& mesh = m_world->getComponent<Mesh>(entity);
        std::shared_ptr<VertexArray> vao = m_vaos[entity];

        m_shader->loadMaterial(mesh.material);
        vao->draw();
    }
}

void SceneRenderer::setScene(ShowcaseScene* scene)
{
    m_scene = scene;
}

ShowcaseScene* SceneRenderer::getScene()
{
    return m_scene;
}

const ShowcaseScene* SceneRenderer::getScene() const
{
    return m_scene;
}

} // namespace texplr
