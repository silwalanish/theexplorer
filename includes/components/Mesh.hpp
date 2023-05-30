#pragma once

#include <cstdint>
#include <vector>

#include <core/Vertex.hpp>
#include <ecs/Component.hpp>

namespace texplr {

struct Mesh : public Component<Mesh> {
public:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    Mesh() = default;
    Mesh(const Mesh& mesh) = default;

    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
        : vertices(vertices)
        , indices(indices)
    {
    }
};

} // namespace texplr
