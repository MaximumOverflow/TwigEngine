//
// Created by max on 02/10/19.
//

#include <Layers/RenderingLayer.h>

#include "Layers/RenderingLayer.h"
#include "Video/Renderer.h"

TE::RenderingLayer::RenderingLayer() : Layer("RenderingLayer") {}

void TE::RenderingLayer::Update() {
//    Renderer::Clear();
    Renderer::DrawQueue();
//    Renderer::SwapBuffers();
}

void TE::RenderingLayer::DisabledUpdate() {
    Renderer::ClearQueue();
}
