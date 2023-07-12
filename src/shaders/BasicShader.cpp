#include <shaders/BasicShader.hpp>

namespace texplr {

static std::string VERTEX_SHADER_SOURCE = R"(
    #version 430

    layout (location = 0) in vec3 POSITION;
    layout (location = 1) in vec3 NORMAL;
    layout (location = 2) in vec2 UV;

    layout (location = 0) out vec4 FRAG_POS;

    uniform mat4 MVP_MAT;

    void main() {
        gl_Position = vec4(POSITION, 1.0);

        FRAG_POS = gl_Position;
    }
)";

static std::string FRAGMENT_SHADER_SOURCE = R"(
    #version 430

    struct Material {
        vec3 color;
    };

    layout (location = 0) in vec4 FRAG_POS;
    layout (location = 0) out vec4 FRAG_COLOR;

    uniform Material MATERIAL;

    bool is_mandelbrot = false;

    float iters = 500.0;
    float scale = 100.0;
    vec2 offset = vec2(-0.5, 0.0);
    float limit = 2;
    float c_real = -0.745; // -2 to 2
    float c_imag = 0.123; // 0 to 1

    float map(float value, float min1, float max1, float min2, float max2) {
        return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
    }

    float get_mandelbrot_set(float real, float img, float c_real, float c_imag, float iters) {
        float cr = real;
        float ci = img;

        real = c_real;
        img = c_imag;
        
        float fractal_color = 0.0;
        for(float i=0.0; i<5000.0; i++) {
            if(i >= iters) break;
            
            float real_prev = real;
            real = real_prev * real_prev - img * img + cr;
            img = 2.0 * real_prev * img + ci;

            if(real*real + img*img > limit*limit) {
                fractal_color = i / iters;
                break;
            }
        }

        return fractal_color;
    }

    float get_julia_set(float real, float img, float c_real, float c_imag, float iters) {
        float fractal_color = 0.0;
        for(float i=0.0; i<5000.0; i++) {
            if(i >= iters) break;

            float real_prev = real;
            real = real_prev * real_prev - img * img + c_real;
            img = 2.0 * real_prev * img + c_imag;

            if(real * real + img * img > limit*limit) {
                fractal_color = i / iters;
                break;
            }
        }

        return fractal_color;
    }

    void main() {
        float scale = 1.0 / scale;

        float real = (FRAG_POS[0]) * scale  + offset.x;
        float img = (FRAG_POS[1]) * scale + offset.y;

        float fractal_color = 0.0;
        if (is_mandelbrot) fractal_color = get_mandelbrot_set(real, img, c_real, c_imag, iters);
        else fractal_color = get_julia_set(real, img, c_real, c_imag, iters);

        float r = map(fractal_color * fractal_color, 0.0, 0.3 * 0.3, 0.0, 1.0);
        float g = map(fractal_color, 0.3, 0.6, 0.0, 1.0);
        float b = map(sqrt(fractal_color), sqrt(0.6), 1.0, 0.0, 1.0);

        vec3 mandelbrot_color = vec3(r, g, b);
        vec4 final_color = vec4(mandelbrot_color, 1.0) * vec4(MATERIAL.color, 1.0);
        FRAG_COLOR = final_color;
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
    m_mvpMatrixLoc = getUniformLocation("MVP_MAT");
    m_materialColorLoc = getUniformLocation("MATERIAL.color");
}

}
