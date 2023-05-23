#include <GL/glew.h>

#include <core/GLEWContext.hpp>
#include <core/GLFWContext.hpp>
#include <core/GameWindow.hpp>

int main()
{
    texplr::GLFWContext glfwContext(4, 3);

    texplr::GameWindow window("The Explorer!", 640, 480);

    // TODO: Cache the window context that can be retrieved later.
    texplr::GLEWContext windowContext(window);

    // Loop until the user closes the window
    while (!window.shouldClose()) {
        // Render here
        glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        window.swapBuffers();

        // Poll for and process events
        glfwContext.pollEvents();
    }

    windowContext.destroy();
    window.destroy();
    glfwContext.destroy();

    return 0;
}
