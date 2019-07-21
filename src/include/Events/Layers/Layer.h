#ifndef TWIG_ENGINE_LAYER_H
#define TWIG_ENGINE_LAYER_H

#include "../Event.h"
#include "../../Modules/EventListener.h"

namespace TE {
    class Layer {
    private:
        Layer *next, *previous;
        std::vector<EventListener*> subscribedListeners;

    public:
        virtual ~Layer() = default;

        bool enabled = true;

        virtual void Update() {};
        virtual void OnEvent(Event* event) {};
        virtual void Notify(Event* event);

        void AddListener(EventListener* eventListener);
        void RemoveListener(EventListener* eventListener);
    };
}
#endif //TWIG_ENGINE_LAYER_H
