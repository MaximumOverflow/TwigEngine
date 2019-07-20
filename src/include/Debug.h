//
// Created by max on 06/07/19.
//

#ifndef TWIG_ENGINE_DEBUG_H
#define TWIG_ENGINE_DEBUG_H

#include <iostream>
#include "Global.h"

namespace TE
{
    class Debug {
    public:
        enum class Severity {
            Info, Warning, Error
        };

        inline static void ToggleDebug(bool state) { Global::Debug = state; }

        static void Log(const std::string message) {
            Log(message, Severity::Info);
        }

        static void Log(const std::string message, Severity severity) {
            if (!Global::Debug) return;

            std::string _message;
            switch (severity)
            {
                case Severity::Info:
                    _message.append("[Info]");
                    break;
                case Severity::Warning:
                    _message.append("[Warning]");
                    break;
                case Severity::Error:
                    _message.append("[Error]");
                    break;
            }
            _message.append((severity == Severity::Warning ? "\t" : "\t\t" )+ message);
            std::cout << _message << '\n';
        }
    };
}

#endif //TWIG_ENGINE_DEBUG_H
