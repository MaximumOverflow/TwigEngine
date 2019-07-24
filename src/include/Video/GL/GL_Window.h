//
// Created by max on 18/07/19.
//

#ifndef TWIG_ENGINE_GL_WINDOW_H
#define TWIG_ENGINE_GL_WINDOW_H

#include "Video/Window.h"
#include <GLFW/glfw3.h>

namespace TE {
    class GL_Window : public Window {
    private:
        GLFWwindow* window;

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

        static void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
                                             GLenum severity, GLsizei length,
                                             const GLchar *msg, const void *data);

    public:
        GL_Window(unsigned int width, unsigned int height, std::string title);
        ~GL_Window() override;

        void SwapBuffers();
        bool IsOpen() override;
        GLFWwindow* GetGLFWWindowPointer();
    };
}
#endif //TWIG_ENGINE_GL_WINDOW_H
