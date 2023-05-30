#pragma once

#include <components/Mesh.hpp>
#include <components/Transform.hpp>
#include <ecs/ScopedSystem.hpp>

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
};

} // namespace texplr
