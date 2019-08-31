#include <utility>

#include "Modules/MeshRenderer.h"
#include "Video/Renderer.h"
using namespace TE;

void MeshRenderer::Update() {
    if (mesh != nullptr)
    {
        Renderer::Draw(GetParent());
    }
}

pShader MeshRenderer::GetShader() const {
    return shader;
}

VertexArrayObject* MeshRenderer::GetMeshVAO() {
    return mesh->GetVAO();
}

pTexture MeshRenderer::GetTexture() const {
    return texture;
}

Transform *MeshRenderer::GetParentTransform() const {
    return parentTransform;
}

MeshRenderer::MeshRenderer(GameObject *parent) : Module(parent) {
    parentTransform = parent->GetModule<Transform>();
    if (parentTransform == nullptr)
        parentTransform = parent->AddModule<Transform>();
}

void MeshRenderer::SetMesh(pMesh mesh) {
    MeshRenderer::mesh = std::move(mesh);
}

void MeshRenderer::SetShader(pShader shader) {
    MeshRenderer::shader = std::move(shader);
}

void MeshRenderer::SetTexture(pTexture texture) {
    MeshRenderer::texture = std::move(texture);
}