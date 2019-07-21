//
// Created by max on 21/07/19.
//

#ifndef TWIG_ENGINE_MODULE_H
#define TWIG_ENGINE_MODULE_H

#include <string>

namespace TE {
    class Module {
    private:
    public:
        Module() = default;
        virtual void Update() {};
    };
}
#endif //TWIG_ENGINE_MODULE_H
