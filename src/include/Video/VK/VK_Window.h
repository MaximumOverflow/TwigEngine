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

        //GLFW Input events
        static void TranslateEvents(GLFWwindow* window, int key, int scancode, int action, int mods); //GLFW Key Events
        static void TranslateEvents(GLFWwindow* window, double xpos, double ypos); //GLFW Mouse Cursor Events
        static void TranslateEventsScroll(GLFWwindow* window, double xScroll, double yScroll); //GLFW Mouse Scroll Events
        static void TranslateEvents(GLFWwindow* window, int button, int action, int mods); //GLFW Mouse Button Events
        //GLFW Window events
        static void TranslateEvents(GLFWwindow *window); //Close
        static void TranslateEvents(GLFWwindow *window, int width, int height); //Resize
        static void TranslateEvents(GLFWwindow *window, int minimized); //Minimize
        static void TranslateEventsMaximize(GLFWwindow *window, int maximized); //Maximize

    public:
        VK_Window(unsigned int width, unsigned int height, std::string title);

        ~VK_Window() override;

        bool IsOpen() override;
    };
}
#endif //TWIG_ENGINE_VK_WINDOW_H
