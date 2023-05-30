#include <systems/SceneRenderer.hpp>

#include <iostream>

namespace texplr {

void SceneRenderer::OnInit()
{
}

void SceneRenderer::OnUpdate(float deltaTime)
{
}

void SceneRenderer::render()
{
    for (EntityHandle entity : m_registeredEntities) {
        const Transform& transform = m_world->getComponent<Transform>(entity);
        const Mesh& mesh = m_world->getComponent<Mesh>(entity);

        std::cout << "Mesh:: " << mesh.vertices.size() << std::endl;
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
