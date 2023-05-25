#pragma once

#include "core/GLEWContext.hpp"
#include "core/GLFWContext.hpp"
#include "core/GameWindow.hpp"

namespace texplr {

class Application {
public:
    Application();
    ~Application();

    void run();

private:
    GLFWContext m_glfwContext;
    GameWindow m_window;
    GLEWContext m_glewContext;
};

} // namespace texplr
