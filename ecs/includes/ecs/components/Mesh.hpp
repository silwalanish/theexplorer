#pragma once

#include <cstdint>
#include <vector>

#include <core/Material.hpp>
#include <core/MeshData.hpp>
#include <ecs/Component.hpp>

namespace texplr {

struct Mesh : public Component<Mesh> {
public:
    MeshData meshData;
    Material material;

    Mesh() = default;
    Mesh(const Mesh& mesh) = default;

    Mesh(const MeshData& meshData, const Material& material)
        : meshData(meshData)
        , material(material)
    {
    }

    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const Material& material)
        : meshData(MeshData { vertices, indices })
        , material(material)
    {
    }
};

} // namespace texplr
