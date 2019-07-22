//
// Created by max on 20/07/19.
//

#ifndef TWIG_ENGINE_EVENTLISTENER_H
#define TWIG_ENGINE_EVENTLISTENER_H

#include "Events/Event.h"
#include "Modules/Module.h"

namespace TE {
    class EventListener : public Module {
    private:
        unsigned long ID;
        std::vector<std::function<void(Event*)>> functionCallbacks;
    public:
        EventListener(GameObject* parent);
        ~EventListener();

        void HandleEvent(Event* event);
        void SetID(unsigned long ID);
        void AddCallback(std::function<void(Event*)> callback);
    };
}



#endif //TWIG_ENGINE_EVENTLISTENER_H
