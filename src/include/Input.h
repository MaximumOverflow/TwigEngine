//
// Created by max on 21/07/19.
//

#ifndef TWIG_ENGINE_INPUT_H
#define TWIG_ENGINE_INPUT_H
#include "Events/Event.h"

namespace TE {
    class Input {
    public:
        static bool GetMouseButtonPressed(Event *event, int button);
        static bool GetMouseButtonReleased(Event *event, int button);
        static bool GetMouseButtonHeld(Event *event, int button);

        static bool GetKeyPressed(Event *event, int key);
        static bool GetKeyPressed(int key);
        static bool GetKeyReleased(Event *event, int key);
        static bool GetKeyReleased(int key);
        static bool GetKeyHeld(Event *event, int key);
        static bool GetKeyHeld(int key);
    };
}

#endif //TWIG_ENGINE_INPUT_H
