//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_SHADER_H
#define TWIG_ENGINE_SHADER_H

#include <string>

namespace TE {
    class Shader {
    public:
        static Shader* Create(std::string vertexSource, std::string fragmentSource);
        static Shader* CreateFromFile(std::string vertexPath, std::string fragmentPath);
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual ~Shader() = default;
    };
}

#endif //TWIG_ENGINE_SHADER_H
