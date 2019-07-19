//
// Created by max on 18/07/19.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../../include/Video/GL/GL_Window.h"
#include "../../../include/Debug.h"

using namespace TE;

GL_Window::GL_Window(unsigned int width, unsigned int height, std::string title) {
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);
    TE::Debug::Log("Initializing OpenGL backend...");
    if (glewInit() != GLEW_OK)
        TE::Debug::Log("Failed to initialize OpenGL", TE::Debug::Severity::Error);
    else
        TE::Debug::Log("OpenGL successfully initialized");
    glfwShowWindow(window);
}


void GL_Window::SwapBuffers() {
    glfwSwapBuffers(window);
}

GL_Window::~GL_Window() {
    glfwDestroyWindow(window);
}

bool GL_Window::IsOpen() {
    return !glfwWindowShouldClose(window);
}
