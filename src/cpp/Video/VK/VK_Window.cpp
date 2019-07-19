//
// Created by max on 18/07/19.
//

#include "../../../include/Video/VK/VK_Window.h"
#include "../../../include/Debug.h"

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
}

VK_Window::~VK_Window() {
    vkDestroyInstance(vkInstance, nullptr);
    glfwDestroyWindow(window);
}

bool VK_Window::IsOpen() {
    return !glfwWindowShouldClose(window);
}
