#pragma once

#include <memory>

#include <core/EventBus.hpp>
#include <core/Events.hpp>
#include <core/GLEWContext.hpp>
#include <core/GLFWContext.hpp>
#include <core/GameWindow.hpp>
#include <core/Scene.hpp>

namespace texplr {

class Application {
public:
    Application();
    ~Application();

    void run();

    std::shared_ptr<EventBus> getEventBus() const;
    std::shared_ptr<Scene> getScene() const;

    void setScene(std::shared_ptr<Scene> scene);

private:
    bool m_running = false;
    std::shared_ptr<EventBus> m_eventBus;

    GLFWContext m_glfwContext;
    GameWindow m_window;
    GLEWContext m_glewContext;

    std::shared_ptr<Scene> m_scene;

    void OnKeyDown(KeyDownEvent* event);
    void OnWindowClose(WindowCloseEvent* event);
};

} // namespace texplr
