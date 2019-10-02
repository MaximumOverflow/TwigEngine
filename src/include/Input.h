//
// Created by max on 21/07/19.
//

#ifndef TWIG_ENGINE_INPUT_H
#define TWIG_ENGINE_INPUT_H

#include "Modules/Listeners/EventListener.h"
#include "Modules/Listeners/InputListener.h"
#include "Events/Event.h"
#include "Layers/InputLayer.h"
#include "Layers/LayerStack.h"

namespace TE {
    class Input {
    private:
        static InputLayer* inputLayer;
    public:
        static void Init();

        static void SetMouseCursorShown(bool active);

        static bool GetMouseButtonPressed(InputEvent *event, int button);
        static bool GetMouseButtonReleased(InputEvent *event, int button);
        static bool GetMouseButtonHeld(InputEvent *event, int button);

        static bool GetKeyPressed(InputEvent *event, int key);
        static bool GetKeyPressed(Event *event, int key);
        static bool GetKeyPressed(int key);
        static bool GetKeyReleased(InputEvent *event, int key);
        static bool GetKeyReleased(Event *event, int key);
        static bool GetKeyReleased(int key);
        static bool GetKeyHeld(InputEvent *event, int key);
        static bool GetKeyHeld(Event *event, int key);
        static bool GetKeyHeld(int key);
    };
}

#endif //TWIG_ENGINE_INPUT_H
