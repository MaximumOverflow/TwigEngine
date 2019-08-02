//
// Created by max on 22/07/19.
//
#include <Modules/MeshRenderer.h>

#include "Modules/MeshRenderer.h"
#include "Video/Renderer.h"
using namespace TE;

void MeshRenderer::SetMesh(Mesh *mesh) {
    this->mesh = mesh;
}

void MeshRenderer::Update() {
    if (mesh != nullptr)
    {
        Renderer::Draw(GetParent());
    }
}

void MeshRenderer::SetShader(Shader *shader) {
    MeshRenderer::shader = shader;
}

Shader* MeshRenderer::GetShader() const {
    return shader;
}

VertexArrayObject* MeshRenderer::GetMeshVAO() {
    return mesh->GetVAO();
}

Texture *MeshRenderer::GetTexture() const {
    return texture;
}

void MeshRenderer::SetTexture(Texture *texture) {
    this->texture = texture;
}

Transform *MeshRenderer::GetParentTransform() const {
    return parentTransform;
}

MeshRenderer::MeshRenderer(GameObject *parent) : Module(parent) {
    parentTransform = parent->GetModule<Transform>();
    if (parentTransform == nullptr)
        parentTransform = parent->AddModule<Transform>();
}
