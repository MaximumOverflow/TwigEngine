//
// Created by max on 21/07/19.
//
#include "../../include/Events/WindowEvents.h"
using namespace TE;

int WindowEvent::GetCategories() {
    return EventCategory::WindowEvent;
}

EventType WindowClosedEvent::GetType() {
    return EventType::WindowClose;
}

EventType WindowResizedEvent::GetType() {
    return EventType::WindowResize;
}

WindowResizedEvent::Size WindowResizedEvent::GetSize() {
    return size;
}

EventType WindowMinimizedEvent::GetType() {
    return EventType::WindowMinimize;
}

bool WindowMinimizedEvent::IsMinimazed() {
    return minimized;
}

EventType WindowMaximizedEvent::GetType() {
    return EventType::WindowMaximize;
}

bool WindowMaximizedEvent::IsMaximized() {
    return maximized;
}
