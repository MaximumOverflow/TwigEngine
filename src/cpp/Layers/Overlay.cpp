//
// Created by max on 21/07/19.
//

#include <Layers/Overlay.h>

#include "Layers/Overlay.h"
#include "Global.h"
#include "Video/Renderer.h"
#include "Debug.h"

#ifndef TE_PLATFORM_MACOS
#include "Video/GL/GL_Window.h"
#include "Video/VK/VK_Window.h"
#include "Debug.h"
#endif

using namespace TE;

bool Overlay::ImGuiInitialized = 0;
unsigned int Overlay::overlayCount = 0;
ImGuiIO* Overlay::io;

TE::Overlay::Overlay() {
    if (!ImGuiInitialized)
        InitializeImGui();

    overlayCount++;
}

Overlay::~Overlay() {
    overlayCount--;
    if(overlayCount == 0)
        TerminateImGui();
}

void Overlay::InitializeImGui() {
    Debug::Log("Initializing ImGui...");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;
//    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

#ifndef TE_PLATFORM_MACOS
    if (Global::activeAPI == GraphicsAPI::OpenGL)
    {
        GLFWwindow* window = ((GL_Window*) Renderer::GetWindow())->GetGLFWWindowPointer();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }
    else /*if (Global::activeAPI == GraphicsAPI::Vulkan)*/
    {
        Debug::Log("Failed to initialize Overlay due to lack of implementation for the current API", Debug::Severity::Error);
//        GLFWwindow* window = ((VK_Window*) Renderer::GetWindow())->GetGLFWWindowPointer();
//        ImGui_ImplGlfw_InitForVulkan(window, true);
//        ImGui_ImplVulkan_InitInfo* initInfo;
//        ImGui_ImplVulkan_Init();
    }
#endif

    ImGuiInitialized = true;
}

void Overlay::TerminateImGui() {
    Debug::Log("Shutting down ImGui...");

#ifndef TE_PLATFORM_MACOS
    if (Global::activeAPI == GraphicsAPI::OpenGL)
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
    }
#endif

    ImGui::DestroyContext();

    ImGuiInitialized = false;
}

void Overlay::NewFrame() {
    if (!ImGuiInitialized) return;
#ifndef TE_PLATFORM_MACOS
if (Global::activeAPI == GraphicsAPI::OpenGL)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
    }
#endif

    ImGui::NewFrame();
}

void Overlay::EndFrame() {
    if (!ImGuiInitialized) return;
    ImGui::Render();
#ifndef TE_PLATFORM_MACOS
if (Global::activeAPI == GraphicsAPI::OpenGL)
    {
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
#endif
}
