//
// Created by max on 21/07/19.
//

#include "Layers/Layer.h"
#include "Events/Event.h"
#include "Modules/EventListener.h"

void TE::Layer::Notify(TE::Event *event) {
    for (EventListener* eventListener : subscribedListeners)
        eventListener->HandleEvent(event);
}

void TE::Layer::AddListener(TE::EventListener *eventListener) {
    subscribedListeners.push_back(eventListener);
}

void TE::Layer::RemoveListener(TE::EventListener *eventListener) {
    for (unsigned long i = 0; i < subscribedListeners.size(); i++)
        if (subscribedListeners.at(i) == eventListener)
        {
            subscribedListeners.erase(subscribedListeners.begin()+i);
            break;
        }
}
