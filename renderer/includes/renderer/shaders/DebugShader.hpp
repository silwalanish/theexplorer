#pragma once

#include <renderer/opengl/Shader.hpp>

namespace texplr {

class DebugShader : public virtual Shader {
public:
    DebugShader();

    virtual void loadSun(const Light& light) override;
    virtual void loadMaterial(const Material& material) override;

private:
    void cacheUniformLocation();
};

} // namespace texplr
