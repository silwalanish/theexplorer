#pragma once

#include <glm/glm.hpp>

namespace texplr {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};

} // namespace texplr
