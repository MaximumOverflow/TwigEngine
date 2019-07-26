//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_GL_SHADER_H
#define TWIG_ENGINE_GL_SHADER_H

#include <stdint-gcc.h>
#include <string>

#include "Video/Shader.h"

namespace TE {
    class GL_Shader : public TE::Shader{
    private:
        unsigned int ID;
        void BuildShader(const char *vertexSrc, const char *fragmentSrc);
    public:
        GL_Shader(const char* vertexSrc, const char* fragmentSrc);
        ~GL_Shader() override;

        void Bind() override;
        void Unbind() override;

        void SetUniformMat4f(std::string name, const TE::Mat4& matrix) override;
        void SetUniformVec3f(std::string name, const TE::Vec3& vec3) override;
        void SetUniformVec4f(std::string name, const Vec4 &vec4) override;
    };
}


#endif //TWIG_ENGINE_GL_SHADER_H
