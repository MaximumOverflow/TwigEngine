//
// Created by max on 18/07/19.
//

#ifndef TWIG_ENGINE_GL_WINDOW_H
#define TWIG_ENGINE_GL_WINDOW_H

#include "../Window.h"

namespace TE {
    class GL_Window : public Window {
    private:
        GLFWwindow* window;
    public:
        GL_Window(unsigned int width, unsigned int height, std::string title);

        ~GL_Window() override;

        void SwapBuffers();

        bool IsOpen() override;
    };
}
#endif //TWIG_ENGINE_GL_WINDOW_H
