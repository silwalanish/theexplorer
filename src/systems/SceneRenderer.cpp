#include <systems/SceneRenderer.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>

#include <components/Camera.hpp>
#include <core/Scene.hpp>
#include <shaders/BasicShader.hpp>

namespace texplr {

static glm::mat4 calculateViewMatrix(const Transform& transform)
{
    glm::quat pitch = glm::angleAxis(glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::quat yaw = glm::angleAxis(glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat roll = glm::angleAxis(glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::quat orientation = glm::normalize(pitch * yaw * roll);
    glm::mat4 cameraRotation = glm::mat4_cast(orientation);
    glm::mat4 cameraTranslation = glm::translate(glm::mat4(1.0f), -transform.position);

    return cameraRotation * cameraTranslation;
}

static glm::mat4 calculateModelMatrix(const Transform& transform)
{
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, transform.position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotation.x), glm::vec3(1.0, 0.0, 0.0));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotation.y), glm::vec3(0.0, 1.0, 0.0));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotation.z), glm::vec3(0.0, 0.0, 1.0));
    modelMatrix = glm::scale(modelMatrix, transform.scale);
    return modelMatrix;
}

void SceneRenderer::OnInit()
{
    m_shader = std::make_shared<BasicShader>();
}

void SceneRenderer::OnUpdate(float deltaTime)
{
    const Camera& camera = m_scene->getWorld()->getComponent<Camera>(m_scene->getActiveCamera());
    const Transform& cameraTransform = m_scene->getWorld()->getComponent<Transform>(m_scene->getActiveCamera());

    m_projectionMatrix = glm::perspective(glm::radians(camera.fov), camera.aspectRatio, camera.near, camera.far);
    m_viewMatrix = calculateViewMatrix(cameraTransform);

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader->use();
}

void SceneRenderer::render()
{
    begin();

    for (EntityHandle entity : m_registeredEntities) {
        const Transform& transform = m_world->getComponent<Transform>(entity);

        m_shader->loadMVPMatrix(m_projectionMatrix * m_viewMatrix * calculateModelMatrix(transform));

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
