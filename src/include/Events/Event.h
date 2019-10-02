//
// Created by max on 20/07/19.
//

#ifndef TWIG_ENGINE_EVENT_H
#define TWIG_ENGINE_EVENT_H

#include "Types/Types.h"

namespace TE {
    class Event {
    public:
        Event() = default;
        virtual ~Event() = default;

        bool handled = false;
        virtual EventType GetType() = 0;
        virtual int GetCategories() = 0;

        inline bool IsOfCategory(EventCategory category) { return (GetCategories() & category) != 0; }
    };

    class InputEvent : public Event {
    public:
        virtual ~InputEvent() = default;
    };

    class ApplicationEvent : public Event {
    public:
        virtual ~ApplicationEvent() = default;
    };
}

#endif //TWIG_ENGINE_EVENT_H
