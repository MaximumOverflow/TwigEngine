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

//        static void ToggleDebug(bool state);

        static void Log(const std::string message) {
            Log(message, Severity::Info);
        }

        static void Log(const std::string message, Severity severity) {
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
                    _message.append("Error]");
                    break;
            }
            _message.append((severity == Severity::Warning ? "\t" : "\t\t" )+ message);
            std::cout << _message << '\n';
        }
    };
}

#endif //TWIG_ENGINE_DEBUG_H
