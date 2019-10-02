//
// Created by max on 21/07/19.
//

#include "Input.h"
#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"
#include "Video/Renderer.h"
#include "Global.h"
#include "TE_Macros.h"

using namespace TE;

InputLayer* Input::inputLayer;

bool Input::GetMouseButtonPressed(InputEvent *event, int button) {
    if (event->GetType() != EventType::MouseButtonPress)
        return false;
    auto* e = static_cast<MouseButtonPressedEvent*>(event);

    return (e->GetButton() == button);
}

bool Input::GetMouseButtonHeld(InputEvent *event, int button) {
    if (event->GetType() != EventType::MouseButtonHold)
        return false;
    auto* e = static_cast<MouseButtonPressedEvent*>(event);

    return (e->GetButton() == button);
}

bool Input::GetMouseButtonReleased(InputEvent *event, int button) {
    if (event->GetType() != EventType::MouseButtonRelease)
        return false;
    auto * e = static_cast<MouseButtonPressedEvent*>(event);

    return (e->GetButton() == button);
}

bool Input::GetKeyPressed(InputEvent *event, int key) {
    if (event->GetType() != EventType::KeyPress)
        return false;
    auto * e = static_cast<KeyPressedEvent*>(event);

    return (e->GetKey() == key);
}

bool Input::GetKeyReleased(InputEvent *event, int key) {
    if (event->GetType() != EventType::KeyRelease)
        return false;
    auto* e = static_cast<KeyPressedEvent*>(event);

    return (e->GetKey() == key);
}

bool Input::GetKeyHeld(InputEvent *event, int key) {
    if (event->GetType() != EventType::KeyHold)
        return false;

    auto* e = static_cast<KeyPressedEvent*>(event);
    return (e->GetKey() == key);
}

bool Input::GetKeyPressed(int key) {
    return (Renderer::GetActiveAPI()->GetKeyState(key) == KeyState::TE_PRESSED);
}

bool Input::GetKeyReleased(int key) {
    return (Renderer::GetActiveAPI()->GetKeyState(key) == KeyState::TE_RELEASED);
}

bool Input::GetKeyHeld(int key) {
    return (Renderer::GetActiveAPI()->GetKeyState(key) != KeyState::TE_RELEASED);
}

void Input::SetMouseCursorShown(bool active) {
    Renderer::GetActiveAPI()->SetMouseCursor(active);
}

void Input::Init() {
    inputLayer = LayerStack::AddLayer(new InputLayer());
}

bool Input::GetKeyPressed(Event *event, int key) {
    return GetKeyPressed((InputEvent*) event, key);
}

bool Input::GetKeyReleased(Event *event, int key) {
    return GetKeyReleased((InputEvent*) event, key);
}

bool Input::GetKeyHeld(Event *event, int key) {
    return GetKeyHeld((InputEvent*) event, key);
}
