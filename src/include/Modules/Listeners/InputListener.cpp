//
// Created by max on 02/10/19.
//

#include <Debug.h>
#include "InputListener.h"

using namespace TE;

Layer* InputListener::inputLayer;

bool InputListener::AllowMultipleInstances() {
    return false;
}

void InputListener::HandleEvent(Event *event) {
    if (dynamic_cast<InputEvent*>(event))
        EventListener::HandleEvent(event);
}

InputListener::InputListener(GameObject *parent) : EventListener(parent) {
    if (!inputLayer)
        inputLayer = LayerStack::GetLayer("InputLayer");
    inputLayer->AddListener(this);
}

InputListener::~InputListener() {
    inputLayer->RemoveListener(this);
}


