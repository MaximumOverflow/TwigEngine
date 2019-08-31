//
// Created by max on 21/07/19.
//
#include "Input.h"
#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"
#include "Video/Renderer.h"
#include "Global.h"
#include "TE_Macros.h"

#ifndef TE_PLATFORM_MACOS
#include "Video/GL/GL_Window.h"
#endif

using namespace TE;

bool Input::GetMouseButtonPressed(TE::Event *event, int button) {
    if (event->GetType() != EventType::MouseButtonPress)
        return false;
    auto* e = static_cast<MouseButtonPressedEvent*>(event);

    return (e->GetButton() == button);
}

bool Input::GetMouseButtonHeld(TE::Event *event, int button) {
    if (event->GetType() != EventType::MouseButtonHold)
        return false;
    auto* e = static_cast<MouseButtonPressedEvent*>(event);

    return (e->GetButton() == button);
}

bool Input::GetMouseButtonReleased(TE::Event *event, int button) {
    if (event->GetType() != EventType::MouseButtonRelease)
        return false;
    auto * e = static_cast<MouseButtonPressedEvent*>(event);

    return (e->GetButton() == button);
}

bool Input::GetKeyPressed(Event *event, int key) {
    if (event->GetType() != EventType::KeyPress)
        return false;
    auto * e = static_cast<KeyPressedEvent*>(event);

    return (e->GetKey() == key);
}

bool Input::GetKeyReleased(Event *event, int key) {
    if (event->GetType() != EventType::KeyRelease)
        return false;
    auto* e = static_cast<KeyPressedEvent*>(event);

    return (e->GetKey() == key);
}

bool Input::GetKeyHeld(Event *event, int key) {
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
