#pragma once

#include <cstdint>
#include <vector>

#include <core/Vertex.hpp>

namespace texplr {

struct MeshData {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};

} // namespace texplr
