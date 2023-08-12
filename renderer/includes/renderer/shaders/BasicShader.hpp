#pragma once

#include <renderer/opengl/Shader.hpp>

namespace texplr {

class BasicShader : public virtual Shader {
public:
    BasicShader();

    virtual void loadSun(const Light& light) override;
    virtual void loadMaterial(const Material& material) override;

private:
    GLuint m_sunColorLoc = 0;
    GLuint m_sunAmbientLoc = 0;
    GLuint m_sunDirectionLoc = 0;
    GLuint m_materialColorLoc = 0;

    void cacheUniformLocation();
};

} // namespace texplr
