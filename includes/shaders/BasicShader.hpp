#pragma once

#include <opengl/Shader.hpp>

namespace texplr {

class BasicShader : public virtual Shader {
public:
    BasicShader();

    virtual void loadMaterial(const Material& material) override;

private:
    GLuint m_materialColorLoc = 0;

    void cacheUniformLocation();
};

} // namespace texplr
