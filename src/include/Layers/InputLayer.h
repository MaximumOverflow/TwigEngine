//
// Created by max on 02/10/19.
//

#ifndef TWIG_ENGINE_INPUTLAYER_H
#define TWIG_ENGINE_INPUTLAYER_H

#include "Layer.h"

namespace TE {
    class InputLayer : public Layer {
    public:
        InputLayer() : Layer("InputLayer") {}
        void Update() override;
        void Notify(Event *event) override;
    };
}

#endif //TWIG_ENGINE_INPUTLAYER_H
