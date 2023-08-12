#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <ecs/components/Camera.hpp>
#include <ecs/components/Transform.hpp>

namespace texplr {

class Math {
public:
    static glm::mat4 calculateProjectionMatrix(const Camera& camera);
    static glm::mat4 calculateViewMatrix(const Transform& transform);
};

} // namespace texplr
