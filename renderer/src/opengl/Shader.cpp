#include <renderer/opengl/Shader.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stdexcept>

namespace texplr {

Shader::Shader()
{
    m_id = glCreateProgram();
}

Shader::~Shader()
{
    if (m_id != 0) {
        glDeleteProgram(m_id);
    }
}

void Shader::use()
{
    glUseProgram(m_id);
}

void Shader::loadProjectionMatrix(const glm::mat4& projectionMatrix)
{
    loadMat4(m_projectionMatrixLoc, projectionMatrix);
}

void Shader::loadViewMatrix(const glm::mat4& viewMatrix)
{
    loadMat4(m_viewMatrixLoc, viewMatrix);
}

void Shader::loadModelMatrix(const glm::mat4& modelMatrix)
{
    loadMat4(m_modelMatrixLoc, modelMatrix);
}

void Shader::loadNormalMatrix(const glm::mat3& normalMatrix)
{
    loadMat3(m_normalMatrixLoc, normalMatrix);
}

void Shader::addVertexShader(const std::string& shaderSource)
{
    m_vertexShader = compileShader(GL_VERTEX_SHADER, shaderSource);
    glAttachShader(m_id, m_vertexShader);
}

void Shader::addFragmentShader(const std::string& shaderSource)
{
    m_fragmentShader = compileShader(GL_FRAGMENT_SHADER, shaderSource);
    glAttachShader(m_id, m_fragmentShader);
}

void Shader::link()
{
    glLinkProgram(m_id);

    GLint isLinked = 0;
    glGetProgramiv(m_id, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &maxLength);

        char* errorLog = new char[maxLength];
        glGetProgramInfoLog(m_id, maxLength, &maxLength, errorLog);

        glDeleteProgram(m_id);
        glDeleteShader(m_vertexShader);
        glDeleteShader(m_fragmentShader);

        m_id = 0;

        std::cerr << "FAILED TO LINK SHADER::" << errorLog << std::endl;

        throw std::runtime_error(errorLog);
    }

    glDetachShader(m_id, m_vertexShader);
    glDetachShader(m_id, m_fragmentShader);

    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);

    m_vertexShader = 0;
    m_fragmentShader = 0;
}

GLuint Shader::compileShader(GLenum shaderType, const std::string& shaderSource)
{
    GLuint shaderId = glCreateShader(shaderType);

    const char* shaderCode = shaderSource.c_str();
    glShaderSource(shaderId, 1, &shaderCode, NULL);
    glCompileShader(shaderId);

    GLint isCompiled = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

        char* errorLog = new char[maxLength];
        glGetShaderInfoLog(shaderId, maxLength, &maxLength, errorLog);

        glDeleteShader(shaderId);

        std::cerr << "FAILED TO COMPILE SHADER::SHADER TYPE(" << shaderType << ")" << std::endl
                  << "Source::" << std::endl
                  << shaderSource << std::endl
                  << errorLog << std::endl;

        throw std::runtime_error(errorLog);
    }

    return shaderId;
}

GLuint Shader::getUniformLocation(const std::string& uniformName)
{
    return glGetUniformLocation(m_id, uniformName.c_str());
}

void Shader::loadFloat(GLuint uniformLoc, const float& value)
{
    glUniform1f(uniformLoc, value);
}

void Shader::loadVec3(GLuint uniformLoc, const glm::vec3& value)
{
    glUniform3f(uniformLoc, value.x, value.y, value.z);
}

void Shader::loadMat3(GLuint uniformLoc, const glm::mat3& value)
{
    glUniformMatrix3fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::loadMat4(GLuint uniformLoc, const glm::mat4& value)
{
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(value));
}

} // namespace texplr
