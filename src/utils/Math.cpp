#include <utils/Math.hpp>

namespace texplr {

glm::mat4 Math::calculateProjectionMatrix(const Camera& camera)
{
    return glm::perspective(glm::radians(camera.fov), camera.aspectRatio, camera.near, camera.far);
}

glm::mat4 Math::calculateViewMatrix(const Transform& transform)
{
    glm::quat pitch = glm::angleAxis(glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::quat yaw = glm::angleAxis(glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat roll = glm::angleAxis(glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::quat orientation = glm::normalize(pitch * yaw * roll);
    glm::mat4 cameraRotation = glm::mat4_cast(orientation);
    glm::mat4 cameraTranslation = glm::translate(glm::mat4(1.0f), -transform.position);

    return cameraRotation * cameraTranslation;
}

} // namespace texplr
