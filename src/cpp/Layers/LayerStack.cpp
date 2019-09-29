//
// Created by max on 21/07/19.
//

#include "Debug.h"
#include "Layers/Layer.h"
#include "Layers/LayerStack.h"

using namespace TE;

std::vector<Layer*> LayerStack::layers;
unsigned long LayerStack::insertLocation;

void LayerStack::Propagate(Event *event) {
    for (auto* layer : layers) {
        if (event->handled)
            return;
        else {
            layer->OnEvent(event);
            layer->Notify(event);
        }
    }
}

void LayerStack::Propagate_Reverse(Event *event) {
    for (long long i = layers.size()-1; i >= 0; i--)
    {
        Layer* layer = layers.at(i);
        if (event->handled)
            return;
        else {
            layer->OnEvent(event);
            layer->Notify(event);
        }
    }
}

Layer* LayerStack::AddLayer(Layer *layer) {
    layers.insert(Begin() + insertLocation++, layer);
    layer->OnAttach();
    return layer;
}

void LayerStack::RemoveLayer(Layer *layer) {
    for (unsigned long i = 0; i < insertLocation; i++)
    {
        if (layers.at(i) == layer)
        {
            layer->OnDetach();
            layers.erase(Begin() + i);
            insertLocation--;
            break;
        }
    }
}

Overlay* LayerStack::AddOverlay(Overlay* overlay) {
    layers.push_back(static_cast<Layer*>(overlay));
    return overlay;
}

void LayerStack::RemoveOverlay(Overlay* overlay) {
    auto* layer = static_cast<Layer*>(overlay);
    for (unsigned long i = insertLocation; i < layers.size(); i++)
    {
        if (layers.at(i) == layer)
        {
            layers.erase(Begin() + i);
            break;
        }
    }
}

void LayerStack::Init() {
    insertLocation = 0;
}

void LayerStack::Clear() {
    for (auto* layer : layers)
        delete layer;
}

void LayerStack::UpdateAll() {
    Overlay::NewFrame();
    for (auto* layer : layers) {
        layer->Update();
    }
    Overlay::EndFrame();
}

const std::vector<Layer*> &LayerStack::GetLayerList() {
    return layers;
}
