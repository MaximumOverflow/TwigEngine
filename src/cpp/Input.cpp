//
// Created by max on 21/07/19.
//

#include <Input.h>

#include "Input.h"

#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"
#include "Video/Renderer.h"
#include "Global.h"

#ifndef TE_PLATFORM_MACOS
#include "Video/GL/GL_Window.h"
#endif

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

bool Input::GetKeyPressed(int key) {
    if (Global::activeAPI == GraphicsAPI::OpenGL)
        return (glfwGetKey(((GL_Window*)(Renderer::GetWindow()))->GetGLFWWindowPointer(), key) == GLFW_PRESS);

    return false;
}

bool Input::GetKeyReleased(int key) {
    if (Global::activeAPI == GraphicsAPI::OpenGL)
        return (glfwGetKey(((GL_Window*)(Renderer::GetWindow()))->GetGLFWWindowPointer(), key) == GLFW_RELEASE);

    return false;
}

bool Input::GetKeyHeld(int key) {
    if (Global::activeAPI == GraphicsAPI::OpenGL)
    {
        return (glfwGetKey(((GL_Window*)(Renderer::GetWindow()))->GetGLFWWindowPointer(), key) != GLFW_RELEASE);
    }

    return false;
}
