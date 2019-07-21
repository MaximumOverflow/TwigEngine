//
// Created by max on 18/07/19.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../../include/Video/GL/GL_Window.h"
#include "../../../include/Debug.h"

#include "../../../include/Events/Event.h"
#include "../../../include/Events/EventHandler.h"
#include "../../../include/Events/MouseEvents.h"
#include "../../../include/Events/KeyboardEvents.h"
#include "../../../include/Events/WindowEvents.h"

using namespace TE;

void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
                                     GLenum severity, GLsizei length,
                                     const GLchar *msg, const void *data)
{
    if (Global::Debug) {
        std::string _source;
        std::string _type;
        std::string _severity;

        switch (source) {
            case GL_DEBUG_SOURCE_API:
                _source = "API";
                break;

            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                _source = "WINDOW SYSTEM";
                break;

            case GL_DEBUG_SOURCE_SHADER_COMPILER:
                _source = "SHADER COMPILER";
                break;

            case GL_DEBUG_SOURCE_THIRD_PARTY:
                _source = "THIRD PARTY";
                break;

            case GL_DEBUG_SOURCE_APPLICATION:
                _source = "APPLICATION";
                break;

            case GL_DEBUG_SOURCE_OTHER:
                _source = "UNKNOWN";
                break;

            default:
                _source = "UNKNOWN";
                break;
        }

        switch (type) {
            case GL_DEBUG_TYPE_ERROR:
                _type = "ERROR";
                break;

            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                _type = "DEPRECATED BEHAVIOR";
                break;

            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                _type = "UDEFINED BEHAVIOR";
                break;

            case GL_DEBUG_TYPE_PORTABILITY:
                _type = "PORTABILITY";
                break;

            case GL_DEBUG_TYPE_PERFORMANCE:
                _type = "PERFORMANCE";
                break;

            case GL_DEBUG_TYPE_OTHER:
                _type = "OTHER";
                break;

            case GL_DEBUG_TYPE_MARKER:
                _type = "MARKER";
                break;

            default:
                _type = "UNKNOWN";
                break;
        }

        switch (severity) {
            case GL_DEBUG_SEVERITY_HIGH:
                _severity = "HIGH";
                break;

            case GL_DEBUG_SEVERITY_MEDIUM:
                _severity = "MEDIUM";
                break;

            case GL_DEBUG_SEVERITY_LOW:
                _severity = "LOW";
                break;

            case GL_DEBUG_SEVERITY_NOTIFICATION:
                _severity = "NOTIFICATION";
                break;

            default:
                _severity = "UNKNOWN";
                break;
        }

        printf("%d: %s of %s severity, raised from %s: %s\n",
               id, _type.c_str(), _severity.c_str(), _source.c_str(), msg);
    }
}

GL_Window::GL_Window(unsigned int width, unsigned int height, std::string title) {
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);
    TE::Debug::Log("Initializing OpenGL backend...");
    if (glewInit() != GLEW_OK)
        TE::Debug::Log("Failed to initialize OpenGL", TE::Debug::Severity::Error);
    else
        TE::Debug::Log("OpenGL successfully initialized");
    glfwShowWindow(window);
    glDebugMessageCallback(GLDebugMessageCallback, nullptr);
    glEnable(GL_DEBUG_OUTPUT);

    Debug::Log("Setting up GLFW callbacks...");
    //Input callbacks
    glfwSetCursorPosCallback(window, TranslateEvents);
    glfwSetMouseButtonCallback(window, TranslateEvents);
    glfwSetKeyCallback(window, TranslateEvents);
    glfwSetScrollCallback(window, TranslateEventsScroll);
    //Window callbacks
    glfwSetWindowCloseCallback(window, TranslateEvents);
    glfwSetWindowSizeCallback(window, TranslateEvents);
    glfwSetWindowIconifyCallback(window, TranslateEvents);
    glfwSetWindowMaximizeCallback(window, TranslateEventsMaximize);
}


void GL_Window::SwapBuffers() {
    glfwSwapBuffers(window);
}

GL_Window::~GL_Window() {
    glfwDestroyWindow(window);
}

bool GL_Window::IsOpen() {
    return !glfwWindowShouldClose(window);
}

void GL_Window::TranslateEvents(GLFWwindow *window, double xpos, double ypos) {
    EventHandler::DispatchEvent(new MouseMovedEvent(xpos, ypos));
}

void GL_Window::TranslateEventsScroll(GLFWwindow *window, double xScroll, double yScroll) {
    EventHandler::DispatchEvent(new MouseScrolledEvent(xScroll, yScroll));
}

void GL_Window::TranslateEvents(GLFWwindow *window, int button, int action, int mods) {
    switch (action)
    {
        case GLFW_PRESS:
            EventHandler::DispatchEvent(new MouseButtonPressedEvent(button));
            break;
        case GLFW_REPEAT:
            EventHandler::DispatchEvent(new MouseButtonHeldEvent(button));
            break;
        case GLFW_RELEASE:
            EventHandler::DispatchEvent(new MouseButtonReleasedEvent(button));
            break;
    }
}

void GL_Window::TranslateEvents(GLFWwindow *window, int key, int scancode, int action, int mods) {
    Event* event;
    switch (action)
    {
        case GLFW_PRESS:
            event = new KeyPressedEvent(key);
            break;
        case GLFW_REPEAT:
            event = new KeyHeldEvent(key);
            break;
        case GLFW_RELEASE:
            event = new KeyReleasedEvent(key);
            break;
    }
    EventHandler::DispatchEvent(event);
}

void GL_Window::TranslateEvents(GLFWwindow *window) {
    EventHandler::DispatchEvent(new WindowClosedEvent());
}

void GL_Window::TranslateEvents(GLFWwindow *window, int width, int height) {
    EventHandler::DispatchEvent(new WindowResizedEvent(width, height));
}

void GL_Window::TranslateEvents(GLFWwindow *window, int minimized) {
    EventHandler::DispatchEvent(new WindowMinimizedEvent((bool)minimized));
}

void GL_Window::TranslateEventsMaximize(GLFWwindow *window, int maximized) {
    EventHandler::DispatchEvent(new WindowMaximizedEvent((bool) maximized));
}
