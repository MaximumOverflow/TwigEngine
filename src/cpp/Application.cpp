//
// Created by max on 06/07/19.
//
#include "Application.h"
#include "Debug.h"
#include "Time.h"
#include "TE_Macros.h"
#include "Events/EventHandler.h"
#include "EntityManager.h"

#include <chrono>

using namespace TE;

void Application::Init() {
    running = true;
    eventListener.AddCallback(TE_BIND_CALLBACK(Application::Close));
    LayerStack::Init();
}

void Application::Execute() {
    Init();
    Start();

    while (running)
    {
        auto start = std::chrono::high_resolution_clock::now();
        Renderer::Clear();

        EventHandler::PollEvents();
        Run();


        EntityManager::UpdateAll();
        LayerStack::UpdateAll();

        Renderer::SwapBuffers();
        auto end = std::chrono::high_resolution_clock::now();

        auto time = end - start;
        Time::deltaTime = (double) std::chrono::duration_cast<std::chrono::milliseconds>(time).count() / 1000;
    }

    //Cleanup
    LayerStack::Clear();
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