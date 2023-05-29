#pragma once

#include <components/Camera.hpp>
#include <components/Transform.hpp>
#include <ecs/Events.hpp>
#include <ecs/ScopedSystem.hpp>

namespace texplr {

class ActiveCameraFinder : public virtual ScopedSystem<Camera, Transform> {
public:
    ActiveCameraFinder();
    virtual ~ActiveCameraFinder();

    virtual void onInit() override;
    virtual void update(float deltaTime) override;
};

} // namespace texplr
