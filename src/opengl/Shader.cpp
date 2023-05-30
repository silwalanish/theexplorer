#include <opengl/Shader.hpp>

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

} // namespace texplr
