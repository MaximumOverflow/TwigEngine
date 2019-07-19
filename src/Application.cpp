//
// Created by max on 06/07/19.
//

#include "include/Application.h"
#include "include/Debug.h"

using namespace TE;

void Application::Execute() {

    Start();

    while (Renderer::WindowIsOpen())
    {
#ifndef TE_PLATFORM_MACOS
        if (Renderer::GetCurrentAPI() == GraphicsAPI::OpenGL || Renderer::GetCurrentAPI() == GraphicsAPI::Vulkan)
        {
            glfwPollEvents();
        }
#endif
        Run();
        Renderer::Run();
    }

    //Cleanup
    Renderer::Terminate();
}

int main() {
    Debug::Log("Initializing application...");
    auto application = TE::SetupApplication();

    if (application == nullptr)
    {
        Debug::Log("Failed to initialize application. Setup function returned a nullptr.", Debug::Severity::Error);
        return -1;
    }

    application->Execute();
    delete application;
}