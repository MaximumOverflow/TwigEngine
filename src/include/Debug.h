//
// Created by max on 06/07/19.
//

#ifndef TWIG_ENGINE_DEBUG_H
#define TWIG_ENGINE_DEBUG_H

#include <iostream>

namespace TE
{
    class Debug {
    public:
        enum class Severity {
            Info, Warning, Error
        };

        static void ToggleDebug(bool state);

        static void Log(const std::string message);

        static void Log(const std::string message, Severity severity);
    };
}

#endif //TWIG_ENGINE_DEBUG_H
