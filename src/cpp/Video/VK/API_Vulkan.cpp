//
// Created by max on 19/08/25.
//
#include "Video/VK/API_Vulkan.h"
#include "Video/VK/VK_Window.h"
#include "Debug.h"

#include <vector>


using namespace TE;

std::shared_ptr<Window> TE::API_Vulkan::CreateWindow(unsigned int width, unsigned int height, std::string title) {
    auto window = std::make_shared<VK_Window>(width, height, title);
    windows.push_back(window);
    return window;
}

void TE::API_Vulkan::Draw(bool wireframe, unsigned int count) {

}

void TE::API_Vulkan::DrawIndexed(bool wireframe, unsigned int count) {

}

void TE::API_Vulkan::Clear() {

}

API_Vulkan::API_Vulkan() {
    Debug::Log("Initializing GLFW...");
    if (!glfwInit())
        Debug::Log("Failed to initialize GLFW", Debug::Severity::Error);

    Debug::Log("Creating Vulkan instance...");

    vkApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    vkApplicationInfo.apiVersion = VK_API_VERSION_1_0;
    vkApplicationInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
    vkApplicationInfo.pEngineName = "TwigEngine";
    vkApplicationInfo.pApplicationName = "TwigEngine Application";
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
}

API_Vulkan::~API_Vulkan() {
    vkDestroyInstance(vkInstance, nullptr);
    glfwTerminate();
}

void API_Vulkan::SwapBuffers() {

}

std::shared_ptr<Window> API_Vulkan::GetCurrentWindow() {
    return windows.at(currentWindow);
}

std::shared_ptr<Window> API_Vulkan::GetWindow(unsigned int index) {
    return windows.at(index);
}

unsigned long API_Vulkan::GetWindowCount() {
    return windows.size();
}

short API_Vulkan::GetKeyState(int key) {
    switch (glfwGetKey(windows.at(currentWindow)->window, key))
    {
        case GLFW_PRESS:
            return KeyState::TE_PRESSED;
        case GLFW_RELEASE:
            return KeyState::TE_RELEASED;
        case GLFW_REPEAT:
            return KeyState::TE_HELD;
        default:
            return KeyState::TE_RELEASED;
    }
}

void API_Vulkan::SetMouseCursor(bool active) {
    glfwSetInputMode(windows.at(currentWindow)->window, GLFW_CURSOR, active ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

