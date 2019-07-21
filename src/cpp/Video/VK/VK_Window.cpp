//
// Created by max on 18/07/19.
//

#include "../../../include/Video/VK/VK_Window.h"
#include "../../../include/Debug.h"

#include "../../../include/Events/EventHandler.h"
#include "../../../include/Events/MouseEvents.h"
#include "../../../include/Events/KeyboardEvents.h"
#include "../../../include/Events/WindowEvents.h"

using namespace TE;

VK_Window::VK_Window(unsigned int width, unsigned int height, std::string title) {

    TE::Debug::Log("Creating Vulkan instance...");

    VkApplicationInfo vkApplicationInfo = {};
    vkApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    vkApplicationInfo.apiVersion = VK_API_VERSION_1_0;
    vkApplicationInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
    vkApplicationInfo.pEngineName = "Twig Engine";
    vkApplicationInfo.engineVersion = VK_MAKE_VERSION(0,1,0);
    vkApplicationInfo.pApplicationName = title.c_str();
    vkApplicationInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);

    VkInstanceCreateInfo vkInstanceCreateInfo = {};
    vkInstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    vkInstanceCreateInfo.pApplicationInfo = &vkApplicationInfo;
    TE::Debug::Log("Loading Vulkan extensions...");
    uint32_t extentionCount;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&extentionCount);
    vkInstanceCreateInfo.enabledExtensionCount = extentionCount;
    vkInstanceCreateInfo.ppEnabledExtensionNames = glfwExtensions;
    vkEnumerateInstanceExtensionProperties(nullptr, &extentionCount, nullptr);
    TE::Debug::Log("Successfully loaded " + std::to_string(extentionCount) + " extensions");

    VkResult vkResult = vkCreateInstance(&vkInstanceCreateInfo, nullptr, &vkInstance);
    if (vkResult == VK_SUCCESS)
        TE::Debug::Log("Successfully created Vulkan instance");
    else
        TE::Debug::Log("Failed to create Vulkan instance", TE::Debug::Severity::Error);

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
    vkDestroyInstance(vkInstance, nullptr);
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