//
// Created by max on 20/07/19.
//

#include "../../include/Events/EventHandler.h"
using namespace TE;
std::vector<TE::EventListener*> EventHandler::eventListeners;

void TE::EventHandler::DispatchEvent(Event *event) {
    for (auto eventListener : eventListeners)
        eventListener->HandleEvent(event);

    delete event;
}

unsigned long EventHandler::AddEventListener(EventListener *eventListener) {
    eventListeners.push_back(eventListener);
    return eventListeners.size()-1;
}

void EventHandler::RemoveEventListener(unsigned long& ID) {
    eventListeners.erase(eventListeners.begin() + ID);
    for (unsigned long i = ID; i < eventListeners.size(); i++)
        eventListeners.at(i)->SetID(i);
}