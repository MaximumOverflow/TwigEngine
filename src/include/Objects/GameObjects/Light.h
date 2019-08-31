//
// Created by max on 25/07/19.
//

#ifndef TWIG_ENGINE_LIGHT_H
#define TWIG_ENGINE_LIGHT_H

#include "Modules/Transform.h"
#include "GameObject.h"

namespace TE {
    class Light : public GameObject {
    private:
        Transform* transform = AddModule<Transform>();
    public:
        enum class LightType { POINT, SPOT, DIRECTIONAL };
        Light(Vec3 position = Vec3(0,0,0), Vec4 color = Vec4(1.f,1.f,1.f,1.f), LightType type = LightType::POINT);
        ~Light();

        Vec4 color;
        double drawDistance = 500;
        LightType type;
    };
}


#endif //TWIG_ENGINE_LIGHT_H
