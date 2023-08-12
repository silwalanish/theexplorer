#include <core/GLFWContext.hpp>

#include <stdexcept>

#include <GLFW/glfw3.h>

namespace texplr {

GLFWContext::GLFWContext(int glMajorVer, int glMinorVer)
{
    if (!glfwInit()) {
        throw std::runtime_error("Couldn't initialize GLFW!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajorVer);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinorVer);

    m_isInitialized = true;
}

GLFWContext::~GLFWContext()
{
}

void GLFWContext::pollEvents()
{
    glfwPollEvents();
}

void GLFWContext::destroy()
{
    if (m_isInitialized) {
        glfwTerminate();

        m_isInitialized = false;
    }
}

} // namespace texplr
