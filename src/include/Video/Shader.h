//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_SHADER_H
#define TWIG_ENGINE_SHADER_H

#include <string>
#include <unordered_map>

#include "Types/Types.h"


namespace TE {
    class Shader {
    protected:
        std::unordered_map<std::string, int> uniformCache;
        int GetUniformFromCache(std::string name);
        void AddUniformToCache(std::string name, int id);
    public:
        static Shader* Create(std::string vertexSource, std::string fragmentSource);
        static Shader* CreateFromFile(std::string vertexPath, std::string fragmentPath);

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void SetUniformMat4f(std::string name, const Mat4& matrix) = 0;
        virtual void SetUniformVec3f(std::string name, const Vec3& vec3) = 0;
        virtual void SetUniformVec4f(std::string name, const Vec4& vec4) = 0;

        Shader() = default;
        virtual ~Shader() = default;
    };
}

#endif //TWIG_ENGINE_SHADER_H
