#pragma once

#include <GLFW/glfw3.h>

namespace texplr {

class GLEWContext {
public:
    GLEWContext(GLFWwindow* window);
    ~GLEWContext();

    void destroy();
};

} // namespace texplr
