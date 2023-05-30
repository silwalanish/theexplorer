#pragma once

#include <glm/glm.hpp>
#include <vector>

#include <ecs/Component.hpp>

namespace texplr {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};

struct Mesh : public Component<Mesh> {
public:
    std::vector<Vertex> vertices;

    Mesh() = default;
    Mesh(const Mesh& mesh) = default;

    Mesh(const std::vector<Vertex>& vertices)
        : vertices(vertices)
    {
    }
};

} // namespace texplr
