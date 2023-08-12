#pragma once

namespace texplr {

class GLFWContext {
public:
    GLFWContext(int glMajorVer, int glMinorVer);
    ~GLFWContext();

    void pollEvents();

    void destroy();

private:
    bool m_isInitialized = false;
};

} // namespace texplr
