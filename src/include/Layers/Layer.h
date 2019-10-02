#include <utility>

#ifndef TWIG_ENGINE_LAYER_H
#define TWIG_ENGINE_LAYER_H

#include "Events/Event.h"
#include "Modules/Listeners/EventListener.h"

namespace TE {
    class Layer {
        friend class LayerStack;
    private:
        std::vector<EventListener*> subscribedListeners;
        void UpdateGeneric();

    protected:
        std::string name;
    public:
        explicit Layer(std::string name) : name{std::move(name)} { Enable(); };
        virtual ~Layer() = default;

        bool enabled;
        virtual void OnEvent(Event* event) {};
        virtual void Notify(Event* event);
        virtual void Update() = 0;
        virtual void DisabledUpdate() {};

        virtual void OnAttach() {};
        virtual void OnDetach() {};
        virtual void OnEnable() {};
        virtual void OnDisable() {};

        void Enable();
        void Disable();

        template <class T>
        T* AddListener(T* eventListener)
        {
            subscribedListeners.push_back(eventListener);
            return eventListener;
        }

        template <class T>
        void RemoveListener(T* eventListener) {
            for (unsigned long i = 0; i < subscribedListeners.size(); i++)
                if (subscribedListeners.at(i) == eventListener)
                {
                    subscribedListeners.erase(subscribedListeners.begin()+i);
                    return;
                }
        }
    };
}
#endif //TWIG_ENGINE_LAYER_H
