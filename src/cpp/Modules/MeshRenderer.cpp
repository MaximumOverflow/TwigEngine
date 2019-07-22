//
// Created by max on 22/07/19.
//
#include "Modules/MeshRenderer.h"
#include "Video/Renderer.h"
using namespace TE;

void MeshRenderer::SetMesh(Mesh *mesh) {
    this->mesh = mesh;
}

void MeshRenderer::Update() {
    if (mesh != nullptr)
    {
        if (shader != nullptr)
            shader->Bind();
        Renderer::Draw(mesh->GetVAO());
        if (shader != nullptr)
            shader->Unbind();
    }
}

void MeshRenderer::SetShader(Shader *shader) {
    MeshRenderer::shader = shader;
}
