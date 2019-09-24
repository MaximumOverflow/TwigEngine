//
// Created by max on 22/07/19.
//

#ifndef TWIG_ENGINE_MESHRENDERER_H
#define TWIG_ENGINE_MESHRENDERER_H

#include "Video/Texture.h"
#include "Objects/Mesh.h"
#include "Video/Shader.h"
#include "Module.h"
#include "Transform.h"
#include "TE_Macros.h"

namespace TE {
    class MeshRenderer : public Module {
    private:
        pMesh mesh = nullptr;
        pShader shader = nullptr;
        pTexture texture = nullptr;
        Transform* parentTransform;
    public:
        double customDrawDistance = 0;

        explicit MeshRenderer(GameObject* parent);
        void SetMesh(pMesh mesh);


        void SetShader(pShader shader);
        pShader GetShader() const;

        void SetTexture(pTexture texture);
        pTexture GetTexture() const;

        VertexArrayObject* GetMeshVAO();
        Transform* GetParentTransform() const;

        void Update() override;

        bool AllowMultipleInstances() override { return true; };
    };
}

#endif //TWIG_ENGINE_MESHRENDERER_H
