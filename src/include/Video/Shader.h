//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_SHADER_H
#define TWIG_ENGINE_SHADER_H

namespace TE {
    class Shader {
    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual ~Shader() = default;
    };
}

#endif //TWIG_ENGINE_SHADER_H
