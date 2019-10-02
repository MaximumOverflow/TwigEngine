//
// Created by max on 19/09/29.
//

#include "ResourceManager.h"
#include "Debug.h"

#include "Objects/Mesh.h"
#include "Video/Texture.h"
#include "Video/Shader.h"

#include <fstream>
#include <vector>
#include <tuple>
#include <ResourceManager.h>


using namespace TE;

std::unordered_map<std::string, std::pair<std::pair<std::string, std::string>, std::shared_ptr<Asset>>> ResourceManager::assets;

void ResourceManager::Init()
{
    std::ifstream databaseFile;
    databaseFile.open("database.tedat");
    if (!databaseFile.is_open())
        return;

    std::vector<std::tuple<std::string, std::string, std::string>> entries;
    std::string line;
    while (std::getline(databaseFile, line))
    {
        if (line.empty()) continue;

        std::string type = line.substr(0, line.find('|'));
        line = line.substr(line.find('|')+1, line.size());
        std::string name = line.substr(0, line.find('|'));
        line = line.substr(line.find('|')+1, line.size());
        std::string path = line.substr(0, line.find('|'));
        line = line.substr(line.find('|')+1, line.size());

        std::pair<std::string, std::string> info(type, path);
        assets[name] = std::pair<std::pair<std::string, std::string>, std::shared_ptr<Asset>>(info, nullptr);
    }
}

std::shared_ptr<Asset> ResourceManager::CreateAsset(std::string name) {
    auto& entry = assets[name];
    auto[type, path] = entry.first;

    if(type == "Mesh")              { entry.second = Mesh::Create(path, FileType::OBJ); }
    else if (type == "Texture")     { entry.second = Texture::Create(path); }
    else if (type == "Shader")      {
        std::string vertexPath, fragmentPath;
        vertexPath = path.substr(0, path.find('&'));
        fragmentPath = path.substr(path.find('&', path.size()));

        entry.second = Shader::CreateFromFile(vertexPath, fragmentPath);
    }

    return entry.second;
}

void ResourceManager::AddAsset(std::string name, std::string type, std::string path) {
    std::pair<std::string, std::string> info(type, path);
    assets[name] = std::pair<std::pair<std::string, std::string>, std::shared_ptr<Asset>>(info, nullptr);
}

void ResourceManager::AddAsset(std::string name, std::shared_ptr<Asset> asset) {

    std::string type;

    if (dynamic_cast<Mesh*>(asset.get()))
         type = "Mesh";
    else if (dynamic_cast<Texture*>(asset.get()))
        type = "Texture";
    else if (dynamic_cast<Shader*>(asset.get()))
        type = "Shader";

    std::pair<std::string, std::string> info(type, "$INTERNAL");
    assets[name] = std::pair<std::pair<std::string, std::string>, std::shared_ptr<Asset>>(info, asset);
}