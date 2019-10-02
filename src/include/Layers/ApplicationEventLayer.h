//
// Created by max on 02/10/19.
//

#ifndef TWIG_ENGINE_APPLICATIONLAYER_H
#define TWIG_ENGINE_APPLICATIONLAYER_H

#include "Layer.h"

namespace TE {
    class ApplicationEventLayer : public Layer {
    public:
        ApplicationEventLayer() : Layer("ApplicationEventLayer") {}
        void Update() override {};

        void Notify(Event* event) override;
    };
}

#endif //TWIG_ENGINE_APPLICATIONLAYER_H
