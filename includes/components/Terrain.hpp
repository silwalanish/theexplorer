#pragma once

#include <core/MeshData.hpp>
#include <ecs\Component.hpp>

namespace texplr {

struct Terrain : public Component<Terrain> {
public:
    Terrain() = default;
    Terrain(const Terrain&) = default;
};

} // namespace texplr
