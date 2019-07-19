//
// Created by max on 18/07/19.
//

#ifndef TWIG_ENGINE_VK_WINDOW_H
#define TWIG_ENGINE_VK_WINDOW_H

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include "../Window.h"

namespace TE {
    class VK_Window : public Window {
    private:
        GLFWwindow* window;
        VkInstance vkInstance;

    public:
        VK_Window(unsigned int width, unsigned int height, std::string title);

        ~VK_Window() override;

        bool IsOpen() override;
    };
}
#endif //TWIG_ENGINE_VK_WINDOW_H
