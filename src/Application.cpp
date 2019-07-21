//
// Created by max on 06/07/19.
//

#include "include/Application.h"
#include "include/Debug.h"
#include "include/TE_Macros.h"

using namespace TE;

void Application::Execute() {
    running = true;
    eventListener.AddCallback(TE_BIND_CALLBACK(Application::Close));
    Start();

    while (running)
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

void Application::Close(Event* event) {
    if (event->GetType() == EventType::WindowClose)
        running = false;
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