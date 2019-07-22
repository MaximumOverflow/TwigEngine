//
// Created by max on 22/07/19.
//

#ifndef TWIG_ENGINE_MESHRENDERER_H
#define TWIG_ENGINE_MESHRENDERER_H

#include "Objects/Mesh.h"
#include "Module.h"

namespace TE {
    class MeshRenderer : public Module {
    private:
        Mesh* mesh;
    public:
        void SetMesh(Mesh* mesh);

        void Update() override;
    };
}

#endif //TWIG_ENGINE_MESHRENDERER_H
