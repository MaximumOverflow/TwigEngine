//
// Created by max on 21/07/19.
//

#ifndef TWIG_ENGINE_LAYERSTACK_H
#define TWIG_ENGINE_LAYERSTACK_H

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

        static Layer* AddLayer(Layer* layer);
        static void RemoveLayer(Layer* layer);
        static Overlay* AddOverlay(Overlay* overlay);
        static void RemoveOverlay(Overlay* overlay);
        static const std::vector<Layer*>& GetLayerList();
    };
}

#endif //TWIG_ENGINE_LAYERSTACK_H
