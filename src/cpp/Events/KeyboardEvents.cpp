//
// Created by max on 21/07/19.
//

#include "../../include/Events/KeyboardEvents.h"
using namespace TE;

int KeyboardEvent::GetCategories() {
    return EventCategory::KeyboardEvent;
}

TE::EventType KeyPressedEvent::GetType() {
    return EventType::KeyPress;
}

TE::EventType KeyHeldEvent::GetType() {
    return EventType::KeyHold;
}

TE::EventType KeyReleasedEvent::GetType() {
    return EventType::KeyRelease;
}
