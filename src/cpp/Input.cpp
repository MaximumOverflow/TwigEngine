//
// Created by max on 21/07/19.
//

#include "../include/Input.h"
#include "../include/Events/MouseEvents.h"
#include "../include/Events/KeyboardEvents.h"
#include "../include/Global.h"

using namespace TE;

bool Input::GetMouseButtonPressed(TE::Event *event, int button) {
    if (event->GetType() != EventType::MouseButtonPress)
        return false;
    MouseButtonPressedEvent* e = static_cast<MouseButtonPressedEvent*>(event);

    return (e->GetButton() == button);
}

bool Input::GetMouseButtonHeld(TE::Event *event, int button) {
    if (event->GetType() != EventType::MouseButtonHold)
        return false;
    MouseButtonPressedEvent* e = static_cast<MouseButtonPressedEvent*>(event);

    return (e->GetButton() == button);
}

bool Input::GetMouseButtonReleased(TE::Event *event, int button) {
    if (event->GetType() != EventType::MouseButtonRelease)
        return false;
    MouseButtonPressedEvent* e = static_cast<MouseButtonPressedEvent*>(event);

    return (e->GetButton() == button);
}

bool Input::GetKeyPressed(Event *event, int key) {
    if (event->GetType() != EventType::KeyPress)
        return false;
    KeyPressedEvent* e = static_cast<KeyPressedEvent*>(event);

    return (e->GetKey() == key);
}

bool Input::GetKeyReleased(Event *event, int key) {
    if (event->GetType() != EventType::KeyRelease)
        return false;
    KeyPressedEvent* e = static_cast<KeyPressedEvent*>(event);

    return (e->GetKey() == key);
}

bool Input::GetKeyHeld(Event *event, int key) {
    if (event->GetType() != EventType::KeyHold)
        return false;

    KeyPressedEvent* e = static_cast<KeyPressedEvent*>(event);
    return (e->GetKey() == key);
}

bool Input::GetKeyHeld(Event *event, int key, bool ignoreOSRepeatCooldown) {
    if (!ignoreOSRepeatCooldown)
    {
        if (event->GetType() != EventType::KeyHold)
            return false;
    }
    else
    {
        if (event->GetType() == EventType::KeyRelease)
            return false;
    }

    KeyPressedEvent* e = static_cast<KeyPressedEvent*>(event);

    return (e->GetKey() == key);
}
