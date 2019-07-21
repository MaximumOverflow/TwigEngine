//
// Created by max on 06/07/19.
//

#ifndef TWIG_ENGINE_TE_APPLICATION_H
#define TWIG_ENGINE_TE_APPLICATION_H

#include "Video/Renderer.h"
#include "Modules/EventListener.h"

namespace TE {
    class Application {
    private:
        bool running;
        EventListener eventListener;
        void Close(Event* event);
        void Init();
    public:
        Application() {};
        virtual ~Application(){};

        void Execute();
        virtual void Run() = 0;
        virtual void Start() = 0;
    };

    extern Application* SetupApplication();
}

#endif //TWIG_ENGINE_TE_APPLICATION_H
