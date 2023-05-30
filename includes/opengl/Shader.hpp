#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

#include <core/Material.hpp>

namespace texplr {

class Shader {
public:
    Shader();
    virtual ~Shader();

    void use();

    virtual void loadMaterial(const Material& material) = 0;

protected:
    GLuint m_id = 0;

    void addVertexShader(const std::string& shaderSource);
    void addFragmentShader(const std::string& shaderSource);

    void link();

    GLuint getUniformLocation(const std::string& uniformName);

    void loadVec3(GLuint uniformLoc, const glm::vec3& value);

private:
    GLuint m_vertexShader = 0;
    GLuint m_fragmentShader = 0;

    GLuint compileShader(GLenum shaderType, const std::string& shaderSource);
};

} // namespace texplr
