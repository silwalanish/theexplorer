#pragma once

#include <glm/glm.hpp>
#include <memory>

#include <components/Mesh.hpp>
#include <components/Transform.hpp>
#include <ecs/EntityHandle.hpp>
#include <ecs/ScopedSystem.hpp>
#include <opengl/Shader.hpp>
#include <opengl/VertexArray.hpp>

namespace texplr {

class Scene;

class SceneRenderer : public virtual ScopedSystem<Transform, Mesh> {
public:
    virtual void OnInit() override;
    virtual void OnUpdate(float deltaTime) override;

    void render();

    void setScene(Scene* scene);

    Scene* getScene();
    const Scene* getScene() const;

private:
    Scene* m_scene = nullptr;
    std::shared_ptr<Shader> m_shader;
    std::map<EntityHandle, std::shared_ptr<VertexArray>> m_vaos;

    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;

    void begin();
};

} // namespace texplr
