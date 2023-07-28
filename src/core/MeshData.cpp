#include <core/MeshData.hpp>

namespace texplr {

void MeshData::recalculateNormals()
{
    uint32_t numFaces = indices.size() / 3;

    for (uint32_t i = 0; i < numFaces; i++) {
        uint32_t aIdx = indices[i * 3];
        uint32_t bIdx = indices[i * 3 + 1];
        uint32_t cIdx = indices[i * 3 + 2];

        Vertex& a = vertices[aIdx];
        Vertex& b = vertices[bIdx];
        Vertex& c = vertices[cIdx];

        glm::vec3 vBMinusA = b.position - a.position;
        glm::vec3 vCMinusA = c.position - a.position;

        glm::vec3 normal = glm::cross(vBMinusA, vCMinusA);
        a.normal = normal;
        b.normal = normal;
        c.normal = normal;
    }
}

} // namespace texplr
