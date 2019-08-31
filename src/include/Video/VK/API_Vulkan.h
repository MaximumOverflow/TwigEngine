//
// Created by max on 19/08/25.
//

#ifndef TWIG_ENGINE_API_VULKAN_H
#define TWIG_ENGINE_API_VULKAN_H

#include "Video/RenderingAPI.h"

#include "Video/VK/VK_Window.h"

#include <vulkan/vulkan.h>

namespace TE
{
    class API_Vulkan : public RenderingAPI {
    private:
        VkInstance vkInstance;
        VkApplicationInfo vkApplicationInfo = {};
        VkInstanceCreateInfo vkInstanceCreateInfo = {};
        VkPhysicalDevice vkPhysicalDevice;

        std::vector<std::shared_ptr<VK_Window>> windows;
    public:
        API_Vulkan();
        ~API_Vulkan();

        std::shared_ptr<Window> CreateWindow(unsigned int width, unsigned int height, std::string title) override;

        void Draw(bool wireframe, unsigned int count) override;
        void DrawIndexed(bool wireframe, unsigned int count) override;
        void Clear() override;

        void SwapBuffers() override;

        std::shared_ptr<Window> GetCurrentWindow() override;
        std::shared_ptr<Window> GetWindow(unsigned int index) override;
        unsigned long GetWindowCount() override;

        short GetKeyState(int key) override;

        void SetMouseCursor(bool active) override;
    };
}

#endif //TWIG_ENGINE_API_VULKAN_H
