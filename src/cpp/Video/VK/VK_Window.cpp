//
// Created by max on 18/07/19.
//

#include <Video/VK/VK_Window.h>

#include "Video/VK/VK_Window.h"
#include "Debug.h"

#include "Events/EventHandler.h"
#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"
#include "Events/WindowEvents.h"

using namespace TE;

VK_Window::VK_Window(unsigned int width, unsigned int height, std::string title) {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    glfwShowWindow(window);

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

VK_Window::~VK_Window() {
    glfwDestroyWindow(window);
}

bool VK_Window::IsOpen() {
    return !glfwWindowShouldClose(window);
}

void VK_Window::TranslateEvents(GLFWwindow *window, double xpos, double ypos) {
    EventHandler::DispatchEvent(new MouseMovedEvent(xpos, ypos));
}

void VK_Window::TranslateEventsScroll(GLFWwindow *window, double xScroll, double yScroll) {
    EventHandler::DispatchEvent(new MouseScrolledEvent(xScroll, yScroll));
}

void VK_Window::TranslateEvents(GLFWwindow *window, int button, int action, int mods) {
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

void VK_Window::TranslateEvents(GLFWwindow *window, int key, int scancode, int action, int mods) {
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

void VK_Window::TranslateEvents(GLFWwindow *window) {
    EventHandler::DispatchEvent(new WindowClosedEvent());
}

void VK_Window::TranslateEvents(GLFWwindow *window, int width, int height) {
    EventHandler::DispatchEvent(new WindowResizedEvent(width, height));
}

void VK_Window::TranslateEvents(GLFWwindow *window, int minimized) {
    EventHandler::DispatchEvent(new WindowMinimizedEvent((bool)minimized));
}

void VK_Window::TranslateEventsMaximize(GLFWwindow *window, int maximized) {
    EventHandler::DispatchEvent(new WindowMaximizedEvent((bool) maximized));
}

GLFWwindow *VK_Window::GetGLFWWindowPointer() {
    return window;
}
