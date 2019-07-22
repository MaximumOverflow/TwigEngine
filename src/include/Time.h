//
// Created by max on 23/07/19.
//

#ifndef TWIG_ENGINE_TIME_H
#define TWIG_ENGINE_TIME_H
namespace TE {
    class Time {
        friend class Application;
    private:
        static double deltaTime;
    public:
        static float DeltaTime() { return deltaTime; };
    };
}



#endif //TWIG_ENGINE_TIME_H
