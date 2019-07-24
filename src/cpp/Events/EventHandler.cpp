//
// Created by max on 20/07/19.
//

#include "Events/EventHandler.h"
#include "Global.h"

#ifndef TE_PLATFORM_MACOS
#include <GLFW/glfw3.h>
#endif

using namespace TE;
std::vector<TE::EventListener*> EventHandler::eventListeners;

void TE::EventHandler::DispatchEvent(Event *event) {
    for (auto eventListener : eventListeners)
    {
        if (event->handled)
            break;
        else
            eventListener->HandleEvent(event);
    }

    LayerStack::Propagate_Reverse(event);

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

void EventHandler::PollEvents() {
#ifndef TE_PLATFORM_MACOS
    if (Global::GetActiveAPI() == GraphicsAPI::OpenGL || Global::GetActiveAPI() == GraphicsAPI::Vulkan)
        glfwPollEvents();
#endif
}
