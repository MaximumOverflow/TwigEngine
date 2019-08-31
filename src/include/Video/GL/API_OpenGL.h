//
// Created by max on 19/08/25.
//

#ifndef TWIG_ENGINE_API_OPENGL_H
#define TWIG_ENGINE_API_OPENGL_H

#include "Video/RenderingAPI.h"

#include "GL_Window.h"
#include "GL_Shader.h"
#include "GL_Texture.h"
#include "GL_VertexArrayObject.h"
#include "GL_IndexBufferObject.h"
#include "GL_FrameBufferObject.h"
#include "GL_VertexBufferObject.h"
#include "GL_Window.h"

#include <vector>

namespace TE {
    class API_OpenGL : public RenderingAPI {
    private:
        std::vector<std::shared_ptr<GL_Window>> windows;
    public:
        API_OpenGL();
        ~API_OpenGL();

        std::shared_ptr<Window> CreateWindow(unsigned int width, unsigned int height, std::string title) override;

        void Draw(bool wireframe, unsigned int count) override;
        void DrawIndexed(bool wireframe, unsigned int count) override;

        void Clear() override;
        void SwapBuffers() override;

        std::shared_ptr<Window> GetCurrentWindow() override;
        std::shared_ptr<Window> GetWindow(unsigned int index) override;
        unsigned long GetWindowCount() override;

        short GetKeyState(int key) override;

        void SetMouseCursor(bool active) override;
    };
}

#endif //TWIG_ENGINE_API_OPENGL_H
