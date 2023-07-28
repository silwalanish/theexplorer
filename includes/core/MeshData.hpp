#pragma once

#include <cstdint>
#include <vector>

#include <core/Vertex.hpp>

namespace texplr {

struct MeshData {
public:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    void recalculateNormals();
};

} // namespace texplr
