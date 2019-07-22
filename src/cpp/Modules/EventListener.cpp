//
// Created by max on 20/07/19.
//

#include "Modules/EventListener.h"
#include "Events/EventHandler.h"
#include "Debug.h"

using namespace TE;

TE::EventListener::EventListener(GameObject* parent) : Module(parent) {
    ID = EventHandler::AddEventListener(this);
    Debug::Log("Generated Event Listener of ID: " + std::to_string(ID));
}

void EventListener::HandleEvent(Event *event) {
    for (auto& function : functionCallbacks)
        function(event);
}

void EventListener::SetID(unsigned long ID) {
    this->ID = ID;
}

EventListener::~EventListener() {
    Debug::Log("Destroying Event Listener of ID: " + std::to_string(ID) + "...");
    EventHandler::RemoveEventListener(ID);
}

void EventListener::AddCallback(std::function<void(Event*)> callback) {
    functionCallbacks.push_back(callback);
}
