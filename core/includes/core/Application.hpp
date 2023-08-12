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
    void stop();

    std::shared_ptr<EventBus> getEventBus() const;
    std::shared_ptr<Scene> getScene() const;
    std::shared_ptr<GameWindow> getWindow() const;

    void setScene(std::shared_ptr<Scene> scene);

private:
    bool m_running = false;
    std::shared_ptr<EventBus> m_eventBus;

    GLFWContext m_glfwContext;
    std::shared_ptr<GameWindow> m_window;
    GLEWContext m_glewContext;

    std::shared_ptr<Scene> m_scene;

    void OnKeyDown(KeyDownEvent* event);
    void OnWindowClose(WindowCloseEvent* event);
};

} // namespace texplr
