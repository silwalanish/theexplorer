#include <renderer/shaders/DebugShader.hpp>

namespace texplr {

static std::string VERTEX_SHADER_SOURCE = R"(
    #version 430

    layout (location = 0) in vec3 POSITION;
    layout (location = 1) in vec3 NORMAL;

    uniform mat4 PROJECTION_MAT;
    uniform mat4 VIEW_MAT;
    uniform mat4 MODEL_MAT;

    layout (location = 0) out vec3 FRAG_NORMAL;

    void main() {
        vec4 worldPosition = MODEL_MAT * vec4(POSITION, 1.0);
        gl_Position = PROJECTION_MAT * VIEW_MAT * worldPosition;

        FRAG_NORMAL = NORMAL;
    }
)";

static std::string FRAGMENT_SHADER_SOURCE = R"(
    #version 430

    layout (location = 0) out vec4 FRAG_COLOR;

    layout (location = 0) in vec3 FRAG_NORMAL;

    void main() {
        FRAG_COLOR = vec4(abs(normalize(FRAG_NORMAL)), 1.0);
    }
)";

DebugShader::DebugShader()
{
    addVertexShader(VERTEX_SHADER_SOURCE);
    addFragmentShader(FRAGMENT_SHADER_SOURCE);
    link();

    cacheUniformLocation();
}

void DebugShader::loadSun(const Light& light)
{
}

void DebugShader::loadMaterial(const Material& material)
{
}

void DebugShader::cacheUniformLocation()
{
    m_projectionMatrixLoc = getUniformLocation("PROJECTION_MAT");
    m_viewMatrixLoc = getUniformLocation("VIEW_MAT");
    m_modelMatrixLoc = getUniformLocation("MODEL_MAT");
}

}
