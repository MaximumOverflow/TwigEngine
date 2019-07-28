//
// Created by max on 22/07/19.
//

#ifndef TWIG_ENGINE_MESHRENDERER_H
#define TWIG_ENGINE_MESHRENDERER_H

#include "Video/Shader.h"
#include "Objects/Mesh.h"
#include "Module.h"

namespace TE {
    class MeshRenderer : public Module {
    private:
        Mesh* mesh = nullptr;
        Shader* shader = nullptr;
    public:
        double customDrawDistance = 0;

        MeshRenderer(GameObject* parent) : Module(parent) {};
        void SetMesh(Mesh* mesh);

        void SetShader(Shader *shader);
        Shader* GetShader() const;

        VertexArrayObject* GetMeshVAO();

        void Update() override;
    };
}

#endif //TWIG_ENGINE_MESHRENDERER_H
