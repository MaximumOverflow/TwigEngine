//
// Created by max on 21/07/19.
//

#include "../../../include/Events/Layers/LayerStack.h"
#include "../../../include/Debug.h"

using namespace TE;

std::vector<Layer*> LayerStack::layers;
unsigned long LayerStack::insertLocation;

void LayerStack::Propagate(Event *event) {
    for (auto* layer : layers) {
        if (event->handled)
            break;
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
            break;
        else {
            layer->OnEvent(event);
            layer->Notify(event);
        }
    }
}

Layer* LayerStack::AddLayer(Layer *layer) {
    layers.insert(Begin() + insertLocation++, layer);
    return layer;
}

void LayerStack::RemoveLayer(Layer *layer) {
    for (unsigned long i = 0; i < insertLocation; i++)
    {
        if (layers.at(i) == layer)
        {
            layers.erase(Begin() + i);
            insertLocation--;
            break;
        }
    }
}

Layer* LayerStack::AddOverlay(Layer *layer) {
    layers.push_back(layer);
    return layer;
}

void LayerStack::RemoveOverlay(Layer *layer) {
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
    for (auto* layer : layers) {
        layer->Update();
    }
}
