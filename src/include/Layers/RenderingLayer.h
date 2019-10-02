//
// Created by max on 02/10/19.
//

#ifndef TWIG_ENGINE_RENDERINGLAYER_H
#define TWIG_ENGINE_RENDERINGLAYER_H

#include "Layers/Layer.h"

namespace TE {
    class RenderingLayer : public Layer{
    public:
        RenderingLayer();
        void Update() override;
        void DisabledUpdate() override;
    };
}

#endif //TWIG_ENGINE_RENDERINGLAYER_H
