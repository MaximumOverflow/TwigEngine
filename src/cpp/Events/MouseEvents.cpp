//
// Created by max on 20/07/19.
//
#include "Events/MouseEvents.h"
using namespace TE;

double MouseEvent::x, MouseEvent::y;

int MouseEvent::GetCategories() {
    return EventCategory::MouseEvent;
}

TE::EventType MouseMovedEvent::GetType() {
    return EventType::MouseMove;
}

Vec2 MouseEvent::GetMousePosition() {
    return TE::Vec2(x, y);
}

EventType MouseButtonPressedEvent::GetType() {
    return EventType::MouseButtonPress;
}

TE::EventType MouseButtonReleasedEvent::GetType() {
    return EventType::MouseButtonRelease;
}

TE::EventType MouseButtonHeldEvent::GetType() {
    return EventType::MouseButtonHold;
}

TE::EventType MouseScrolledEvent::GetType() {
    return EventType::MouseScroll;
}
