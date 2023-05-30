#include <shaders/BasicShader.hpp>

namespace texplr {

static std::string VERTEX_SHADER_SOURCE = R"(
    #version 430

    layout (location = 0) in vec3 POSITION;
    layout (location = 1) in vec3 NORMAL;
    layout (location = 2) in vec2 UV;

    void main() {
        gl_Position = vec4(POSITION, 1.0);
    }
)";

static std::string FRAGMENT_SHADER_SOURCE = R"(
    #version 430

    struct Material {
        vec3 color;
    };

    layout (location = 0) out vec4 FRAG_COLOR;

    uniform Material MATERIAL;

    void main() {
        FRAG_COLOR = vec4(MATERIAL.color, 1.0);
    }
)";

BasicShader::BasicShader()
{
    addVertexShader(VERTEX_SHADER_SOURCE);
    addFragmentShader(FRAGMENT_SHADER_SOURCE);
    link();

    cacheUniformLocation();
}

void BasicShader::loadMaterial(const Material& material)
{
    loadVec3(m_materialColorLoc, material.color);
}

void BasicShader::cacheUniformLocation()
{
    m_materialColorLoc = getUniformLocation("MATERIAL.color");
}

}
