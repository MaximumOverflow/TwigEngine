//
// Created by max on 02/10/19.
//

#include "Layers/ApplicationEventLayer.h"

using namespace TE;

void ApplicationEventLayer::Notify(Event *event) {
    if (dynamic_cast<ApplicationEvent*>(event))
        Layer::Notify(event);
}
