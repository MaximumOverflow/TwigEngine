//
// Created by max on 21/07/19.
//

#ifndef TWIG_ENGINE_LAYERSTACK_H
#define TWIG_ENGINE_LAYERSTACK_H

#include <Debug.h>
#include "Layer.h"
#include "Overlay.h"

namespace TE {
    class LayerStack {
    private:
        static std::vector<Layer*> layers;

        static inline std::vector<Layer*>::iterator Begin() { return layers.begin(); }
        static inline std::vector<Layer*>::iterator End() { return layers.end(); }
        static unsigned long insertLocation;

    public:
        static void Init();
        static void Clear();

        static void Propagate(Event* event);
        static void Propagate_Reverse(Event* event);
        static void UpdateAll();

        template <class T>  static T* AddLayer(T* layer)
        {
            auto layersList = GetLayersOfType<T>();
            if (!layersList.empty())
                layer->name += std::to_string(layersList.size());

            layers.insert(Begin() + insertLocation++, layer);
            layer->OnAttach();

            return layer;
        };

        template <class T>
        static auto GetLayersOfType()
        {
            std::vector<T*> results;
            for(auto* layer : layers)
                if (auto lp = dynamic_cast<T*>(layer))
                    results.push_back(lp);

            return results;
        }

        static void RemoveLayer(Layer* layer);
        static Overlay* AddOverlay(Overlay* overlay);
        static void RemoveOverlay(Overlay* overlay);
        static const std::vector<Layer*>& GetLayerList();
        static Layer* GetLayer(std::string name);
    };
}

#endif //TWIG_ENGINE_LAYERSTACK_H
