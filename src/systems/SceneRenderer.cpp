#include <systems/SceneRenderer.hpp>

#include <iostream>

#include <shaders/BasicShader.hpp>

namespace texplr {

void SceneRenderer::OnInit()
{
    m_shader = std::make_shared<BasicShader>();
}

void SceneRenderer::OnUpdate(float deltaTime)
{
    for (EntityHandle entity : m_registeredEntities) {
        if (m_vaos.find(entity) != m_vaos.end()) {
            continue;
        }

        const Mesh& mesh = m_world->getComponent<Mesh>(entity);
        std::shared_ptr<VertexArray> vao = std::make_shared<VertexArray>();
        vao->loadMeshData(mesh.meshData);

        m_vaos[entity] = vao;
    }
}

void SceneRenderer::begin()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // TODO: Enable and clear depth buffer

    m_shader->use();
}

void SceneRenderer::render()
{
    begin();

    // TODO: Load camera matrix.
    for (EntityHandle entity : m_registeredEntities) {
        // TODO: Load transform matrix.
        // const Transform& transform = m_world->getComponent<Transform>(entity);

        const Mesh& mesh = m_world->getComponent<Mesh>(entity);
        std::shared_ptr<VertexArray> vao = m_vaos[entity];

        m_shader->loadMaterial(mesh.material);
        vao->draw();
    }
}

void SceneRenderer::setScene(Scene* scene)
{
    m_scene = scene;
}

Scene* SceneRenderer::getScene()
{
    return m_scene;
}

const Scene* SceneRenderer::getScene() const
{
    return m_scene;
}

} // namespace texplr
