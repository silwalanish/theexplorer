#include <shaders/BasicShader.hpp>

namespace texplr {

static std::string VERTEX_SHADER_SOURCE = R"(
    #version 430

    layout (location = 0) in vec3 POSITION;
    layout (location = 1) in vec3 NORMAL;
    layout (location = 2) in vec2 UV;

    uniform mat4 PROJECTION_MAT;
    uniform mat4 VIEW_MAT;
    uniform mat4 MODEL_MAT;
    uniform mat3 NORMAL_MAT;

    layout (location = 0) out vec3 FRAG_POS;
    layout (location = 1) out vec3 FRAG_NORMAL;
    layout (location = 2) out vec2 FRAG_UV;

    void main() {
        vec4 worldPosition = MODEL_MAT * vec4(POSITION, 1.0);
        gl_Position = PROJECTION_MAT * VIEW_MAT * worldPosition;
        
        FRAG_POS =  worldPosition.xyz / worldPosition.w;
        FRAG_NORMAL = NORMAL_MAT * NORMAL;
        FRAG_UV = UV;
    }
)";

static std::string FRAGMENT_SHADER_SOURCE = R"(
    #version 430

    struct Material {
        vec3 color;
    };

    struct Light {
        float ambient;
        vec3 color;
        vec3 direction;
    };

    layout (location = 0) in vec3 FRAG_POS;
    layout (location = 1) in vec3 FRAG_NORMAL;
    layout (location = 2) in vec2 FRAG_UV;

    layout (location = 0) out vec4 FRAG_COLOR;

    uniform Material MATERIAL;
    uniform Light SUN;

    void main() {
        float diffuse = max(dot(-normalize(SUN.direction), normalize(FRAG_NORMAL)), SUN.ambient);

        FRAG_COLOR = vec4(MATERIAL.color * SUN.color * diffuse, 1.0);
    }
)";

BasicShader::BasicShader()
{
    addVertexShader(VERTEX_SHADER_SOURCE);
    addFragmentShader(FRAGMENT_SHADER_SOURCE);
    link();

    cacheUniformLocation();
}

void BasicShader::loadSun(const Light& light)
{
    loadFloat(m_sunAmbientLoc, light.ambient);
    loadVec3(m_sunColorLoc, light.color);
    loadVec3(m_sunDirectionLoc, light.direction);
}

void BasicShader::loadMaterial(const Material& material)
{
    loadVec3(m_materialColorLoc, material.color);
}

void BasicShader::cacheUniformLocation()
{
    m_projectionMatrixLoc = getUniformLocation("PROJECTION_MAT");
    m_viewMatrixLoc = getUniformLocation("VIEW_MAT");
    m_modelMatrixLoc = getUniformLocation("MODEL_MAT");
    m_normalMatrixLoc = getUniformLocation("NORMAL_MAT");
    m_sunColorLoc = getUniformLocation("SUN.color");
    m_sunAmbientLoc = getUniformLocation("SUN.ambient");
    m_sunDirectionLoc = getUniformLocation("SUN.direction");
    m_materialColorLoc = getUniformLocation("MATERIAL.color");
}

}
