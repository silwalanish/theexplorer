#include <core/GameWindow.hpp>

#include <stdexcept>

#include <core/Events.hpp>

namespace texplr {

static void keyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods)
{
    GameWindow* window = static_cast<GameWindow*>(glfwGetWindowUserPointer(handle));

    if (action == GLFW_PRESS) {
        window->getEventBus()->notify(new KeyDownEvent { KeyCodes(key) });
    } else if (action == GLFW_RELEASE) {
        window->getEventBus()->notify(new KeyUpEvent { KeyCodes(key) });
    }
}

static void closeCallback(GLFWwindow* handle)
{
    GameWindow* window = static_cast<GameWindow*>(glfwGetWindowUserPointer(handle));
    window->getEventBus()->notify(new WindowCloseEvent { window });
}

static void mouseMoveCallback(GLFWwindow* handle, double xpos, double ypos)
{
    GameWindow* window = static_cast<GameWindow*>(glfwGetWindowUserPointer(handle));
    window->getEventBus()->notify(new MouseMoveEvent { glm::vec2(xpos, ypos) });
}

static void mouseButtonCallback(GLFWwindow* handle, int button, int action, int mods)
{
    GameWindow* window = static_cast<GameWindow*>(glfwGetWindowUserPointer(handle));

    if (action == GLFW_PRESS) {
        window->getEventBus()->notify(new MouseButtonDownEvent { MouseButtons(button) });
    } else if (action == GLFW_RELEASE) {
        window->getEventBus()->notify(new MouseButtonUpEvent { MouseButtons(button) });
    }
}

static void mouseScrollCallback(GLFWwindow* handle, double xoffset, double yoffset)
{
    GameWindow* window = static_cast<GameWindow*>(glfwGetWindowUserPointer(handle));
    window->getEventBus()->notify(new MouseScrollEvent { glm::vec2(xoffset, yoffset) });
}

GameWindow::GameWindow(std::shared_ptr<EventBus> eventBus, const std::string& title)
    : m_title(title)
    , m_eventBus(eventBus)
{
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    m_width = mode->width;
    m_height = mode->height;

    m_handle = glfwCreateWindow(static_cast<int>(m_width), static_cast<int>(m_height), m_title.c_str(), monitor, nullptr);

    if (!m_handle) {
        throw new std::runtime_error("Couldn't create a window!");
    }

    init();
}

GameWindow::GameWindow(std::shared_ptr<EventBus> eventBus, const std::string& title, uint16_t width, uint16_t height)
    : m_title(title)
    , m_width(width)
    , m_height(height)
    , m_eventBus(eventBus)
{
    m_handle = glfwCreateWindow(static_cast<int>(m_width), static_cast<int>(m_height), m_title.c_str(), nullptr, nullptr);

    if (!m_handle) {
        throw new std::runtime_error("Couldn't create a window!");
    }

    init();
}

GameWindow::~GameWindow()
{
}

void GameWindow::init()
{
    glfwSetWindowUserPointer(m_handle, this);
    glfwSetKeyCallback(m_handle, &keyCallback);
    glfwSetWindowCloseCallback(m_handle, &closeCallback);
    glfwSetCursorPosCallback(m_handle, &mouseMoveCallback);
    glfwSetMouseButtonCallback(m_handle, &mouseButtonCallback);
    glfwSetScrollCallback(m_handle, &mouseScrollCallback);

    glfwSetCursorPos(m_handle, 0, 0);
}

void GameWindow::swapBuffers()
{
    glfwSwapBuffers(m_handle);
}

void GameWindow::destroy()
{
    if (m_handle) {
        glfwDestroyWindow(m_handle);
        m_handle = nullptr;
    }
}

void GameWindow::lockMouse()
{
    glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(m_handle, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
}

void GameWindow::unlockMouse()
{
    glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

bool GameWindow::isMouseLocked()
{
    return glfwGetInputMode(m_handle, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
}

std::shared_ptr<EventBus> GameWindow::getEventBus() const
{
    return m_eventBus;
}

} // namespace texplr
