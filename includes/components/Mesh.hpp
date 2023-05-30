#pragma once

#include <vector>

#include <core/Vertex.hpp>
#include <ecs/Component.hpp>

namespace texplr {

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
