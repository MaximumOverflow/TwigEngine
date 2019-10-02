//
// Created by max on 21/07/19.
//

#ifndef TWIG_ENGINE_KEYBOARDEVENTS_H
#define TWIG_ENGINE_KEYBOARDEVENTS_H

#include "Event.h"

namespace TE {
    class KeyboardEvent : public InputEvent
    {
    public:
        int GetCategories() override;
    };

    class KeyPressedEvent : public KeyboardEvent
    {
    private:
        int key;
    public:
        explicit KeyPressedEvent(int key) :  key{key} {}
        EventType GetType() override;
        inline int GetKey() { return key; }
    };

    class KeyHeldEvent : public KeyboardEvent
    {
    private:
        int key;
    public:
        explicit KeyHeldEvent(int key) :  key{key} {}
        EventType GetType() override;
        inline int GetKey() { return key; }
    };

    class KeyReleasedEvent : public KeyboardEvent
    {
    private:
        int key;
    public:
        explicit KeyReleasedEvent(int key) :  key{key} {}
        EventType GetType() override;
        inline int GetKey() { return key; }
    };
}

#endif //TWIG_ENGINE_KEYBOARDEVENTS_H
