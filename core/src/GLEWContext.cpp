#include <core/GLEWContext.hpp>

#include <GL/glew.h>

#include <stdexcept>

namespace texplr {

GLEWContext::GLEWContext(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Couldn't initialize GLEW!");
    }
}

GLEWContext::~GLEWContext()
{
}

void GLEWContext::destroy()
{
}

} // namespace texplr
