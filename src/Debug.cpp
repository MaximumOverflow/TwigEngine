//
// Created by max on 23/07/19.
//
#include "Debug.h"
#include "Global.h"

void TE::Debug::ToggleDebug(bool state) {
    Global::Debug = state;
}

void TE::Debug::Log(const std::string message) {
    Log(message, Severity::Info);
}

void TE::Debug::Log(const std::string message, TE::Debug::Severity severity) {
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
