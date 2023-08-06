#pragma once

#include <components/Transform.hpp>
#include <ecs/ScopedSystem.hpp>

namespace texplr {

class TransformSystem : public virtual ScopedSystem<Transform> {
public:
    virtual void OnInit() override;
    virtual void OnUpdate(float deltaTime) override;

private:
    void OnTransformAdded(ComponentAddedEvent<Transform>* event);

    void processTree(EntityHandle root, const Transform& globalTransform);

    void calculateLocalMatrix(Transform& transform);
    void calculateModelMatrix(Transform& transform, const Transform& parentTransform);
    void calculateDirections(Transform& transform);

    void recalculateTransform(Transform& transform, const Transform& parentTransform);
};

} // namespace texplr
