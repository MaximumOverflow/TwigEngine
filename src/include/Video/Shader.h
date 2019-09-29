//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_SHADER_H
#define TWIG_ENGINE_SHADER_H

#include <string>
#include <unordered_map>
#include <memory>

#include "Types/Types.h"
#include "External/robin_hood.h"
#include "Asset.h"

namespace TE {
    class Shader : public Asset {
    protected:
        robin_hood::unordered_map<std::string, int> uniformCache;
        int GetUniformFromCache(std::string name);
        void AddUniformToCache(std::string name, int id);
    public:
        static std::shared_ptr<Shader> Create(std::string vertexSource, std::string fragmentSource);
        static std::shared_ptr<Shader> CreateFromFile(std::string vertexPath, std::string fragmentPath);

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void SetUniformMat4f(std::string name, const Mat4& matrix) = 0;
        virtual void SetUniformVec3f(std::string name, const Vec3& vec3) = 0;
        virtual void SetUniformVec4f(std::string name, const Vec4& vec4) = 0;
        virtual void SetUniformVec1i(std::string name, int vec1) = 0;

        Shader() = default;
        virtual ~Shader() = default;
    };
}

#endif //TWIG_ENGINE_SHADER_H
