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

namespace TE {
    class MeshRenderer : public Module {
    private:
        Mesh* mesh = nullptr;
        Shader* shader = nullptr;
        Texture* texture = nullptr;
        Transform* parentTransform;
    public:
        double customDrawDistance = 0;

        explicit MeshRenderer(GameObject* parent);
        void SetMesh(Mesh* mesh);

        void SetShader(Shader *shader);
        Shader* GetShader() const;

        void SetTexture(Texture* texture);
        Texture* GetTexture() const;

        VertexArrayObject* GetMeshVAO();
        Transform* GetParentTransform() const;

        void Update() override;
    };
}

#endif //TWIG_ENGINE_MESHRENDERER_H
