//
// Created by max on 19/08/25.
//

#include <GL/glew.h>

#include "Video/GL/API_OpenGL.h"
#include "Debug.h"

using namespace TE;

TE::API_OpenGL::API_OpenGL() {
    Debug::Log("Initializing GLFW...");
    if (!glfwInit())
        Debug::Log("Failed to initialize GLFW", Debug::Severity::Error);
}
TE::API_OpenGL::~API_OpenGL() {
    for (auto& window : windows)
        glfwDestroyWindow(window->GetGLFWWindowPointer());
    glfwTerminate();
}


void TE::API_OpenGL::Draw(bool wireframe, unsigned int count) {
    glDrawArrays(wireframe ? GL_LINES : GL_TRIANGLES, 0, count);
}

void TE::API_OpenGL::DrawIndexed(bool wireframe, unsigned int count) {
    glDrawElements(wireframe ? GL_LINES : GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}

std::shared_ptr<Window> TE::API_OpenGL::CreateWindow(unsigned int width, unsigned int height, std::string title) {
    auto window = std::make_shared<GL_Window>(width, height, title);
    windows.push_back(window);
    return window;
}

void API_OpenGL::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void API_OpenGL::SwapBuffers() {
    windows.at(currentWindow)->SwapBuffers();
}

std::shared_ptr<Window> API_OpenGL::GetCurrentWindow() {
    return windows.at(currentWindow);
}

std::shared_ptr<Window> API_OpenGL::GetWindow(unsigned int index) {
    return windows.at(index);
}

unsigned long API_OpenGL::GetWindowCount() {
    return windows.size();
}

short API_OpenGL::GetKeyState(int key) {
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

void API_OpenGL::SetMouseCursor(bool active) {
    glfwSetInputMode(windows.at(currentWindow)->window, GLFW_CURSOR, active ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}
