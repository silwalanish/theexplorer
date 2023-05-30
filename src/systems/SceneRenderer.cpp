#include <systems/SceneRenderer.hpp>

#include <iostream>

namespace texplr {

void SceneRenderer::OnInit()
{
    // TODO: Initialize shaders.
}

void SceneRenderer::OnUpdate(float deltaTime)
{
    for (EntityHandle entity : m_registeredEntities) {
        if (m_vaos.find(entity) != m_vaos.end()) {
            continue;
        }

        const Mesh& mesh = m_world->getComponent<Mesh>(entity);
        std::shared_ptr<VertexArray> vao = std::make_shared<VertexArray>();
        vao->loadVertices(mesh.vertices);

        m_vaos[entity] = vao;
    }
}

void SceneRenderer::begin()
{
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // TODO: Enable and clear depth buffer
}

void SceneRenderer::render()
{
    begin();
    // TODO: Use custom shader.
    // TODO: Load camera matrix.
    for (EntityHandle entity : m_registeredEntities) {
        // TODO: Load transform matrix.
        // const Transform& transform = m_world->getComponent<Transform>(entity);

        std::shared_ptr<VertexArray> vao = m_vaos[entity];
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
