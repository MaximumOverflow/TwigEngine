//
// Created by max on 20/07/19.
//

#ifndef TWIG_ENGINE_MOUSEEVENTS_H
#define TWIG_ENGINE_MOUSEEVENTS_H

#include "Event.h"
#include "Types/Types.h"

#include <glm/glm.hpp>

namespace TE {
    class MouseEvent : public InputEvent
    {
    protected:
        static double x, y;
    public:
        int GetCategories() override;
        static Vec2 GetMousePosition();
    };

    class MouseMovedEvent : public MouseEvent
    {
    public:
        inline MouseMovedEvent (double x, double y) {
            MouseEvent::x = x;
            MouseEvent::y = y;
        }
        EventType GetType() override;
    };

    class MouseButtonPressedEvent : public MouseEvent
    {
    private:
        int button;
    public:
        inline explicit MouseButtonPressedEvent(int button) :  button{button} {}
        EventType GetType() override;
        inline int GetButton() { return button; }
    };

    class MouseButtonReleasedEvent : public MouseEvent
    {
    private:
        int button;
    public:
        inline MouseButtonReleasedEvent(int button ): button{button} {}
        EventType GetType() override;
        inline int GetButton() { return button; }
    };

    class MouseButtonHeldEvent : public MouseEvent
    {
    private:
        int button;
    public:
        inline MouseButtonHeldEvent(int button) : button{button} {}
        EventType GetType() override;
        inline int GetButton() { return button; }
    };

    class MouseScrolledEvent : public MouseEvent
    {
    private:
        double scrollX, scrollY;
    public:
        inline MouseScrolledEvent(double scrollX, double scrollY) :  scrollX{scrollX}, scrollY{scrollY} {}
        EventType GetType() override;
        inline glm::vec2 GetScrolling() { return glm::vec2(scrollX, scrollY); }
    };
}



#endif //TWIG_ENGINE_MOUSEEVENTS_H
