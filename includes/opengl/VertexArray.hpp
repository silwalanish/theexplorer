#pragma once

#include <GL/glew.h>
#include <cstdint>
#include <vector>

#include <core/MeshData.hpp>
#include <core/Vertex.hpp>

namespace texplr {

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void loadMeshData(const MeshData& meshData);

    void bind();
    void draw();

private:
    GLuint m_id = 0;
    GLuint m_vbo = 0;
    GLuint m_ibo = 0;

    GLsizei m_vertexCount = 0;

    void loadVertices(const std::vector<Vertex>& vertices);
    void loadIndices(const std::vector<uint32_t>& indices);
};

} // namespace texplr
