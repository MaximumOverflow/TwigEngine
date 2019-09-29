//
// Created by max on 19/08/25.
//

#ifndef TWIG_ENGINE_RENDERINGAPI_H
#define TWIG_ENGINE_RENDERINGAPI_H

#include "Types/Types.h"
#include "Types/KeyCodes.h"
#include "Window.h"

#include <memory>
#include <vector>

namespace TE {
    class RenderingAPI {
    protected:
        unsigned int currentWindow = 0;
    public:
        virtual std::shared_ptr<Window> CreateWindow(unsigned int width = 1280, unsigned int height = 720, std::string title = "TwingEngine Window") = 0;

        virtual void Draw(bool wireframe, unsigned int count = 0) = 0;
        virtual void DrawIndexed(bool wireframe, unsigned int count = 0) = 0;

        virtual void Clear() = 0;
        virtual void SwapBuffers() = 0;

        virtual std::shared_ptr<Window> GetCurrentWindow() = 0;
        virtual std::shared_ptr<Window> GetWindow(unsigned int index) = 0;
        virtual unsigned long GetWindowCount() = 0;

        virtual short GetKeyState(int key) = 0;
        virtual void SetMouseCursor(bool active) = 0;

        virtual ~RenderingAPI() = default;
    };
}


#endif //TWIG_ENGINE_RENDERINGAPI_H
