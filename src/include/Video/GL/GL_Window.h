//
// Created by max on 18/07/19.
//

#ifndef TWIG_ENGINE_GL_WINDOW_H
#define TWIG_ENGINE_GL_WINDOW_H

#include "Video/Window.h"
#include <GLFW/glfw3.h>

namespace TE {
    class GL_Window : public Window {
        friend class API_OpenGL;
    private:
        GLFWwindow* window;

        //GLFW Input events
        static void OnKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void OnCursorEvent(GLFWwindow *window, double xpos, double ypos);
        static void OnScrollEvent(GLFWwindow *window, double xScroll, double yScroll);
        static void OnMouseButtonEvent(GLFWwindow *window, int button, int action, int mods);
        //GLFW Window events
        static void OnWindowCloseEvent(GLFWwindow *window);
        static void OnWindowResizeEvent(GLFWwindow *window, int width, int height);
        static void OnWindowMinimizeEvent(GLFWwindow *window, int minimized);
        static void OnWindowMaximizeEvent(GLFWwindow *window, int maximized);

        static void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
                                             GLenum severity, GLsizei length,
                                             const GLchar *msg, const void *data);

    public:
        GL_Window(unsigned int width, unsigned int height, std::string title);
        ~GL_Window() override;

        void SwapBuffers();
        bool IsOpen() override;
        GLFWwindow* GetGLFWWindowPointer() const;
    };
}
#endif //TWIG_ENGINE_GL_WINDOW_H
