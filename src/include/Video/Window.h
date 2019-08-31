//
// Created by max on 18/07/19.
//

#ifndef TWIG_ENGINE_WINDOW_H
#define TWIG_ENGINE_WINDOW_H

#include <string>

namespace TE {
    class Window {
    public:
        unsigned int ID;
        unsigned int width, height;
        std::string title;

        virtual ~Window() = default;
        virtual bool IsOpen() = 0;
    };
}
#endif //TWIG_ENGINE_WINDOW_H
