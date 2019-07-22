//
// Created by max on 21/07/19.
//

#ifndef TWIG_ENGINE_GAMEOBJECT_H
#define TWIG_ENGINE_GAMEOBJECT_H

#include <vector>

#include "Debug.h"

namespace TE {
    class Module;
    class GameObject {
    protected:
        std::vector<Module*> modules;
    public:
        GameObject();
        ~GameObject();
        std::string name;
        bool enabled = true;

        void UpdateModules();
        template <typename T>
        T* AddModule() {
            T* module = new T(this);
            Module* mod = dynamic_cast<Module*>(module);
            if (mod)
                modules.push_back(mod);
            else
                Debug::Log("The provided class does not derive from Module", Debug::Severity::Warning);
            return module;
        }


        void RemoveModule(Module* module);

        template <typename T>
        T* GetModule() {
            for (auto &m : modules) {
                T* module = dynamic_cast<T*>(m);
                if (module)
                    return module;
            }
            return nullptr;
        };

        template <typename T>
        std::vector<T*> GetModules() {
            std::vector<T*> _modules;
            for (auto &m : modules) {
                T* module = dynamic_cast<T*>(m);
                if (module)
                    modules.push_back(module);
            }
            return modules;
        }

        virtual void Update() {};
        virtual void TimedUpdate() {};
    };
}

#endif //TWIG_ENGINE_GAMEOBJECT_H
