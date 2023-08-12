#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

#include <core/Light.hpp>
#include <core/Material.hpp>

namespace texplr {

class Shader {
public:
    Shader();
    virtual ~Shader();

    void use();

    virtual void loadSun(const Light& light) = 0;
    virtual void loadMaterial(const Material& material) = 0;
    virtual void loadProjectionMatrix(const glm::mat4& projectionMatrix);
    virtual void loadViewMatrix(const glm::mat4& viewMatrix);
    virtual void loadModelMatrix(const glm::mat4& modelMatrix);
    virtual void loadNormalMatrix(const glm::mat3& normalMatrix);

protected:
    GLuint m_id = 0;
    GLuint m_projectionMatrixLoc = 0;
    GLuint m_viewMatrixLoc = 0;
    GLuint m_modelMatrixLoc = 0;
    GLuint m_normalMatrixLoc = 0;

    void addVertexShader(const std::string& shaderSource);
    void addFragmentShader(const std::string& shaderSource);

    void link();

    GLuint getUniformLocation(const std::string& uniformName);

    void loadFloat(GLuint uniformLoc, const float& value);
    void loadVec3(GLuint uniformLoc, const glm::vec3& value);
    void loadMat3(GLuint uniformLoc, const glm::mat3& value);
    void loadMat4(GLuint uniformLoc, const glm::mat4& value);

private:
    GLuint m_vertexShader = 0;
    GLuint m_fragmentShader = 0;

    GLuint compileShader(GLenum shaderType, const std::string& shaderSource);
};

} // namespace texplr
