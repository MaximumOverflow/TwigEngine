//
// Created by max on 20/07/19.
//

#ifndef TWIG_ENGINE_MOUSEEVENTS_H
#define TWIG_ENGINE_MOUSEEVENTS_H

#include "Event.h"
#include "../Types/Types.h"
#include <glm/glm.hpp>

class MouseEvent : public TE::Event
{
public:
    int GetCategories() override;
};

class MouseMovedEvent : public MouseEvent
{
protected:
    double x, y;
public:
    inline MouseMovedEvent (double x, double y) : x{x}, y{y} {}
    TE::EventType GetType() override;
};

class MouseButtonPressedEvent : public MouseEvent
{
private:
    int button;
public:
    inline explicit MouseButtonPressedEvent(int button) :  button{button} {}
    TE::EventType GetType() override;
    inline int GetButton() { return button; }
};

class MouseButtonReleasedEvent : public MouseEvent
{
private:
    int button;
public:
    inline MouseButtonReleasedEvent(int button ): button{button} {}
    TE::EventType GetType() override;
    inline int GetButton() { return button; }
};

class MouseButtonHeldEvent : public MouseEvent
{
private:
    int button;
public:
    inline MouseButtonHeldEvent(int button) : button{button} {}
    TE::EventType GetType() override;
    inline int GetButton() { return button; }
};

class MouseScrolledEvent : public MouseEvent
{
private:
    double scrollX, scrollY;
public:
    inline MouseScrolledEvent(double scrollX, double scrollY) :  scrollX{scrollX}, scrollY{scrollY} {}
    TE::EventType GetType() override;
    inline glm::vec2 GetScrolling() { return glm::vec2(scrollX, scrollY); }
};

#endif //TWIG_ENGINE_MOUSEEVENTS_H
