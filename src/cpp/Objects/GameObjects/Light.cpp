//
// Created by max on 25/07/19.
//

#include <Video/Renderer.h>
#include <Objects/GameObjects/Light.h>

#include "Objects/GameObjects/Light.h"

TE::Light::Light(Vec3 position, Vec4 color) : color(color) {
    transform->SetPosition(position);
    Renderer::AddLight(this);
}

TE::Light::~Light() {
    Renderer::RemoveLight(this);
}
