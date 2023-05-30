#include <shaders/BasicShader.hpp>

namespace texplr {

static std::string VERTEX_SHADER_SOURCE = R"(
    #version 430

    layout (location = 0) in vec3 POSITION;
    layout (location = 1) in vec3 NORMAL;
    layout (location = 2) in vec2 UV;

    layout (location = 0) out vec3 COLOR;

    void main() {
        gl_Position = vec4(POSITION, 1.0);
        COLOR = (2.0 * POSITION + 1.0) / 2.0;
    }
)";

static std::string FRAGMENT_SHADER_SOURCE = R"(
    #version 430

    layout (location = 0) in vec3 COLOR;

    layout (location = 0) out vec4 FRAG_COLOR;

    void main() {
        FRAG_COLOR = vec4(COLOR, 1.0);
    }
)";

BasicShader::BasicShader()
{
    addVertexShader(VERTEX_SHADER_SOURCE);
    addFragmentShader(FRAGMENT_SHADER_SOURCE);
    link();
}

}
