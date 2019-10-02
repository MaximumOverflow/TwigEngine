//
// Created by max on 02/10/19.
//

#include <Debug.h>
#include "Layers/InputLayer.h"

void TE::InputLayer::Update() {}

void TE::InputLayer::Notify(TE::Event *event) {
    auto inputEvent = dynamic_cast<InputEvent*>(event);
    if (inputEvent)
    {
        Layer::Notify(event);
        event->handled = true;
    }
}
