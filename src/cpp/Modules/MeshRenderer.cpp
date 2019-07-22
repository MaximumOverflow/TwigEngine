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
    Renderer::Draw(mesh->GetVAO());
}
