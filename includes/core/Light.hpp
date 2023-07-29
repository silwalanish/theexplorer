#pragma once

#include <glm/glm.hpp>

namespace texplr {

struct Light {
    float ambient;

    glm::vec3 color;
    glm::vec3 direction;
};

} // namespace texplr
