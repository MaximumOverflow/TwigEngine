//
// Created by max on 21/07/19.
//

#ifndef TWIG_ENGINE_KEYBOARDEVENTS_H
#define TWIG_ENGINE_KEYBOARDEVENTS_H

#include "Event.h"

class KeyboardEvent : public TE::Event
{
public:
    int GetCategories() override;
};

class KeyPressedEvent : public KeyboardEvent
{
    private:
        int key;
    public:
        inline KeyPressedEvent(int key) :  key{key} {}
        TE::EventType GetType() override;
        inline int GetKey() { return key; }
};

class KeyHeldEvent : public KeyboardEvent
{
private:
    int key;
public:
    inline KeyHeldEvent(int key) :  key{key} {}
    TE::EventType GetType() override;
    inline int GetKey() { return key; }
};

class KeyReleasedEvent : public KeyboardEvent
{
private:
    int key;
public:
    inline KeyReleasedEvent(int key) :  key{key} {}
    TE::EventType GetType() override;
    inline int GetKey() { return key; }
};
#endif //TWIG_ENGINE_KEYBOARDEVENTS_H
