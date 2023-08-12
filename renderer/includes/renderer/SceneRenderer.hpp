#pragma once

#include <glm/glm.hpp>
#include <memory>

#include <core/EntityHandle.hpp>
#include <ecs/ScopedSystem.hpp>
#include <ecs/components/Mesh.hpp>
#include <ecs/components/Transform.hpp>
#include <renderer/opengl/Shader.hpp>
#include <renderer/opengl/VertexArray.hpp>

namespace texplr {

class RenderableScene;

class SceneRenderer : public virtual ScopedSystem<Transform, Mesh> {
public:
    virtual void OnInit() override;
    virtual void OnUpdate(float deltaTime) override;

    void render();

    void setScene(RenderableScene* scene);

    RenderableScene* getScene();
    const RenderableScene* getScene() const;

private:
    RenderableScene* m_scene = nullptr;
    std::shared_ptr<Shader> m_shader;
    std::map<EntityHandle, std::shared_ptr<VertexArray>> m_vaos;

    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;

    void begin();
};

} // namespace texplr
