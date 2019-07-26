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
        Light(Vec3 position = Vec3(0,0,0), Vec4 color = Vec4(1.f,1.f,1.f,1.f));
        ~Light();

        Vec4 color;
    };
}


#endif //TWIG_ENGINE_LIGHT_H
