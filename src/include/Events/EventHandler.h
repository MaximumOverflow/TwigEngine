//
// Created by max on 20/07/19.
//

#ifndef TWIG_ENGINE_EVENTHANDLER_H
#define TWIG_ENGINE_EVENTHANDLER_H

#include "Event.h"
#include "Modules/Listeners/EventListener.h"
#include "Layers/LayerStack.h"

namespace TE {
    class EventHandler {
    private:
        static std::vector<EventListener*> eventListeners;
        static unsigned long eventListenerCount;
    public:
        static void DispatchEvent(Event* event);
        static unsigned long AddEventListener(EventListener* eventListener);
        static void RemoveEventListener(unsigned long& ID);
        static void PollEvents();
    };
}

#endif //TWIG_ENGINE_EVENTHANDLER_H