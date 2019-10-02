//
// Created by max on 02/10/19.
//

#ifndef TWIG_ENGINE_INPUTLISTENER_H
#define TWIG_ENGINE_INPUTLISTENER_H

#include "EventListener.h"
#include "Layers/LayerStack.h"


namespace TE {
    class InputListener : public EventListener {
    private:
        static Layer* inputLayer;
    public:
        explicit InputListener(GameObject* parent = nullptr);
        ~InputListener() override;
        bool AllowMultipleInstances() override;

        void HandleEvent(Event *event) override;
    };
}


#endif //TWIG_ENGINE_INPUTLISTENER_H
