#pragma once

#include <GL/glew.h>
#include <vector>

#include <core/Vertex.hpp>

namespace texplr {

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void loadVertices(const std::vector<Vertex>& vertices);

    void bind();
    void draw();

private:
    GLuint m_id = 0;
    GLuint m_vbo = 0;

    GLsizei m_vertexCount = 0;
};

} // namespace texplr
