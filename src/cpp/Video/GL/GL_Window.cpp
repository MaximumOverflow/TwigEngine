//
// Created by max on 18/07/19.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Video/GL/GL_Window.h"
#include "Debug.h"
#include "Global.h"
#include "Video/Renderer.h"

#include "Events/Event.h"
#include "Events/EventHandler.h"
#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"
#include "Events/WindowEvents.h"

using namespace TE;

void APIENTRY GL_Window::GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
                                     GLenum severity, GLsizei length,
                                     const GLchar *msg, const void *data)
{
    if (Global::GetDebugState()) {
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
                return;
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
    Debug::Log("Creating new OpenGL window...");

//    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);
    TE::Debug::Log("Initializing OpenGL backend...");
    if (glewInit() != GLEW_OK)
        TE::Debug::Log("Failed to initialize OpenGL", TE::Debug::Severity::Error);
    else
        TE::Debug::Log("OpenGL successfully initialized");
    glfwShowWindow(window);

    glClearColor(0.0f, 0.0f, 0.3f, 0.0f);

    glDebugMessageCallback(GLDebugMessageCallback, nullptr);
    glEnable(GL_DEBUG_OUTPUT);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);



    Debug::Log("Setting up GLFW callbacks...");
    //Input callbacks
    glfwSetCursorPosCallback(window, OnCursorEvent);
    glfwSetMouseButtonCallback(window, OnMouseButtonEvent);
    glfwSetKeyCallback(window, OnKeyEvent);
    glfwSetScrollCallback(window, OnScrollEvent);
    //Window callbacks
    glfwSetWindowCloseCallback(window, OnWindowCloseEvent);
    glfwSetWindowSizeCallback(window, OnWindowResizeEvent);
    glfwSetWindowIconifyCallback(window, OnWindowMinimizeEvent);
    glfwSetWindowMaximizeCallback(window, OnWindowMaximizeEvent);


    this->width = width;
    this->height = height;
    this->title = title;

    glfwSetCursorPos(window, width/2,height/2);
    Debug::Log("OpenGL window successfully created");
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

void GL_Window::OnCursorEvent(GLFWwindow *window, double xpos, double ypos) {
    EventHandler::DispatchEvent(new MouseMovedEvent(xpos, ypos));
}

void GL_Window::OnScrollEvent(GLFWwindow *window, double xScroll, double yScroll) {
    EventHandler::DispatchEvent(new MouseScrolledEvent(xScroll, yScroll));
}

void GL_Window::OnMouseButtonEvent(GLFWwindow *window, int button, int action, int mods) {
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

void GL_Window::OnKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods) {
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

void GL_Window::OnWindowCloseEvent(GLFWwindow *window) {
    EventHandler::DispatchEvent(new WindowClosedEvent());
}

void GL_Window::OnWindowResizeEvent(GLFWwindow *window, int width, int height) {
    EventHandler::DispatchEvent(new WindowResizedEvent(width, height));
    glViewport(0,0, width, height);
//    glScissor(0,0,width,height);
    Renderer::GetActiveWindow()->width = static_cast<unsigned int>(width);
    Renderer::GetActiveWindow()->height = static_cast<unsigned int>(height);
    Renderer::UpdateCameraProjections();
}

void GL_Window::OnWindowMinimizeEvent(GLFWwindow *window, int minimized) {
    EventHandler::DispatchEvent(new WindowMinimizedEvent((bool)minimized));
}

void GL_Window::OnWindowMaximizeEvent(GLFWwindow *window, int maximized) {
    EventHandler::DispatchEvent(new WindowMaximizedEvent((bool) maximized));
}

GLFWwindow* GL_Window::GetGLFWWindowPointer() const {
    return window;
}
