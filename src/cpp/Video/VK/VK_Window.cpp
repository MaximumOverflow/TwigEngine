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

    Debug::Log("Creating Vulkan instance...");

    vkApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    vkApplicationInfo.apiVersion = VK_API_VERSION_1_0;
    vkApplicationInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
    vkApplicationInfo.pEngineName = "Twig Engine";
    vkApplicationInfo.pApplicationName = title.c_str();
    vkApplicationInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);

    vkInstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    vkInstanceCreateInfo.pApplicationInfo = &vkApplicationInfo;
    Debug::Log("Loading Vulkan extensions...");
    uint32_t extentionCount;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&extentionCount);
    vkInstanceCreateInfo.enabledExtensionCount = extentionCount;
    vkInstanceCreateInfo.ppEnabledExtensionNames = glfwExtensions;
    vkEnumerateInstanceExtensionProperties(nullptr, &extentionCount, nullptr);
    Debug::Log("Successfully loaded " + std::to_string(extentionCount) + " extensions");

    VkResult vkResult = vkCreateInstance(&vkInstanceCreateInfo, nullptr, &vkInstance);
    if (vkResult == VK_SUCCESS)
        Debug::Log("Successfully created Vulkan instance");
    else
        Debug::Log("Failed to create Vulkan instance", Debug::Severity::Error);

    Debug::Log("Generating Vulkan physical devices list...");
    unsigned int physicalDeviceCount;
    vkEnumeratePhysicalDevices(vkInstance, &physicalDeviceCount, nullptr);
    std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
    vkEnumeratePhysicalDevices(vkInstance, &physicalDeviceCount, physicalDevices.data());
    Debug::Log("Found " + std::to_string(physicalDeviceCount) + " physical " + (physicalDeviceCount==1 ? "device" : "devices"));

    Debug::Log("Checking physical devices for Vulkan compatibility...");
    unsigned int score = 0;
    VkPhysicalDeviceProperties physicalDeviceProperties;
    for (auto& device : physicalDevices)
    {
        VkPhysicalDeviceFeatures physicalDeviceFeatures;
        unsigned int deviceScore = 0;

        vkGetPhysicalDeviceProperties(device, &physicalDeviceProperties);
        vkGetPhysicalDeviceFeatures(device, &physicalDeviceFeatures);

        if (!physicalDeviceFeatures.geometryShader)
            continue;

        if (physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            deviceScore+=1000;

        deviceScore += physicalDeviceProperties.limits.maxImageDimension2D * 10;

        if (deviceScore > score)
        {
            score = deviceScore;
            vkPhysicalDevice = device;
        }
    }
    Debug::Log("Using " + std::string(physicalDeviceProperties.deviceName) + " as Vulkan rendering device");

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

GLFWwindow *VK_Window::GetGLFWWindowPointer() {
    return window;
}
