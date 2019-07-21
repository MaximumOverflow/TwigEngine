//
// Created by max on 21/07/19.
//

#ifndef TWIG_ENGINE_WINDOWEVENTS_H
#define TWIG_ENGINE_WINDOWEVENTS_H

#include <glm/vec2.hpp>
#include "Event.h"

namespace TE {
    class WindowEvent : public Event {
    public:
        int GetCategories() override;
    };

    class WindowClosedEvent : public WindowEvent
    {
    public:
        EventType GetType() override;
    };

    class WindowResizedEvent : public WindowEvent
    {
    private:
        struct Size {int w, h;};
        Size size;
    public:
        WindowResizedEvent(int width, int height) : size{width, height} {}
        EventType GetType() override;
        Size GetSize();
    };

    class WindowMinimizedEvent : public WindowEvent
    {
    private:
        bool minimized;
    public:
        WindowMinimizedEvent(bool minimized) : minimized{minimized} {};
        EventType GetType() override;
        bool IsMinimazed();
    };

    class WindowMaximizedEvent : public WindowEvent
    {
    private:
        bool maximized;
    public:
        WindowMaximizedEvent(bool maximized) : maximized{maximized} {};
        EventType GetType() override;
        bool IsMaximized();
    };
}
#endif //TWIG_ENGINE_WINDOWEVENTS_H
