//
// Created by max on 21/07/19.
//

#ifndef TWIG_ENGINE_MODULE_H
#define TWIG_ENGINE_MODULE_H

#include <string>

namespace TE {
    class Module {
    public:
        virtual void Start() {};
        virtual void Update() {};
    };
}
#endif //TWIG_ENGINE_MODULE_H
