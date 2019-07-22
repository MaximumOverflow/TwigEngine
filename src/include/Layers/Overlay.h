//
// Created by max on 21/07/19.
//

#ifndef TWIG_ENGINE_OVERLAY_H
#define TWIG_ENGINE_OVERLAY_H

#include "Layer.h"

#include "External/ImGui/imgui.h"
#include "External/ImGui/imgui_internal.h"

#ifndef TE_PLATFORM_MACOS
    #include "External/ImGui/imgui_impl_glfw.h"
    #include "External/ImGui/imgui_impl_opengl3.h"
    #include "External/ImGui/imgui_impl_vulkan.h"
#endif
#ifdef TE_PLATFORM_WINDOWS
#include "External/ImGui/imgui_impl_dx12.h"
#endif

namespace TE {
    class Overlay : public Layer {
    protected:
        static bool ImGuiInitialized;
        static unsigned int overlayCount;
        static ImGuiIO* io;

        static void InitializeImGui();
        static void TerminateImGui();

        Overlay();
        virtual ~Overlay();

    public:
        static void NewFrame();
        static void EndFrame();
        static unsigned int GetOverlayCount() { return overlayCount; };


    };
}


#endif //TWIG_ENGINE_OVERLAY_H
