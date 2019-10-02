//
// Created by max on 19/09/29.
//

#ifndef TWIG_ENGINE_RESOURCEMANAGER_H
#define TWIG_ENGINE_RESOURCEMANAGER_H

#include <unordered_map>
#include <memory>

#include "Asset.h"
#include "Debug.h"

namespace TE {
    class ResourceManager {
        friend class Application;
    private:
        static std::unordered_map<std::string, std::pair<std::pair<std::string, std::string>, std::shared_ptr<Asset>>> assets;
        static void Init();
        static std::shared_ptr<Asset> CreateAsset(std::string name);
    public:
        template<typename T>
        static std::shared_ptr<T> GetAsset(std::string name) {
            if (assets.find(name) == assets.end())
            {
                Debug::Log("Resource " + name + " could not be found", Debug::Severity::Warning);
                return nullptr;
            }

            auto& entry = assets[name];
            if (!entry.second)
                CreateAsset(name);

            if (dynamic_cast<T*>(entry.second.get()) != nullptr)
                return std::dynamic_pointer_cast<T>(entry.second);
            else
            {
                Debug::Log("Resource " + name + " doesn't match the provided type", Debug::Severity::Warning);
                return nullptr;
            }
        }

        static void AddAsset(std::string name, std::string type, std::string path);
        static void AddAsset(std::string name, std::shared_ptr<Asset> asset);
    };
}

#endif //TWIG_ENGINE_RESOURCEMANAGER_H
