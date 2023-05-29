#pragma once

#include <memory>

#include <core/GLEWContext.hpp>
#include <core/GLFWContext.hpp>
#include <core/GameWindow.hpp>
#include <ecs/World.hpp>

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

    std::shared_ptr<World> m_world;
};

} // namespace texplr
