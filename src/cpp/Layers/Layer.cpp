//
// Created by max on 21/07/19.
//

#include <Layers/Layer.h>

#include "Layers/Layer.h"
#include "Events/Event.h"
#include "Modules/Listeners/EventListener.h"

void TE::Layer::Notify(TE::Event *event) {
    for (EventListener* eventListener : subscribedListeners)
        eventListener->HandleEvent(event);
}

void TE::Layer::UpdateGeneric() {
    if (enabled)    Update();
    else            DisabledUpdate();
}

void TE::Layer::Enable() {
    enabled = true;
    OnEnable();
}

void TE::Layer::Disable() {
    enabled = false;
    OnDisable();
}
