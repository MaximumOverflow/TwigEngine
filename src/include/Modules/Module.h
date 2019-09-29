//
// Created by max on 21/07/19.
//

#ifndef TWIG_ENGINE_MODULE_H
#define TWIG_ENGINE_MODULE_H

#include <string>

namespace TE {
    class GameObject;
    class Module {
    private:
        GameObject* parent;
    public:
        Module(GameObject* parent) : parent{parent} {};
        virtual ~Module() = default;
        GameObject* GetParent();
        virtual void Update() {};
        virtual bool AllowMultipleInstances() = 0;
    };
}
#endif //TWIG_ENGINE_MODULE_H
