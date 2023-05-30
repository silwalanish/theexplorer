#pragma once

#include <GL/glew.h>
#include <string>

namespace texplr {

class Shader {
public:
    Shader();
    virtual ~Shader();

    void use();

protected:
    GLuint m_id = 0;

    void addVertexShader(const std::string& shaderSource);
    void addFragmentShader(const std::string& shaderSource);

    void link();

private:
    GLuint m_vertexShader = 0;
    GLuint m_fragmentShader = 0;

    GLuint compileShader(GLenum shaderType, const std::string& shaderSource);
};

} // namespace texplr
