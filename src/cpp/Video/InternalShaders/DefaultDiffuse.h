//
// Created by max on 01/10/19.
//

#ifndef TWIG_ENGINE_DEFAULTDIFFUSE_H
#define TWIG_ENGINE_DEFAULTDIFFUSE_H

#include "Global.h"

#define LIGHTS std::to_string(Global::GetMaxSimultaneousLightsCount())

namespace TE {
    std::pair<std::string, std::string> s_DefaultDiffuse()
    {
        std::string vertex = {
                "#version 330 core\n"
                "\n"
                "layout (location = 0) in vec3 te_position;\n"
                "layout (location = 1) in vec2 te_texture_position;\n"
                "layout (location = 2) in vec3 te_normal;\n"
                "\n"
                "uniform mat4 te_projection, te_view, te_model;\n"
                "uniform vec3 te_light_position[" + LIGHTS + "]\n;"
                "uniform vec4 te_light_color[" + LIGHTS + "];\n"
                "\n"
                "out vec3 te_frag_normal, te_frag_position;\n"
                "out vec2 te_frag_texture_position;\n"
                "\n"
                "void main()\n"
                "{\n"
                "   vec4 pos = (te_projection * te_view * te_model) * vec4(te_position, 1.0);\n"
                "   gl_Position = pos;\n"
                "   te_frag_position = vec3(te_model * vec4(te_position, 1.0));\n"
                "   te_frag_normal = vec3(mat3(te_model) * te_normal);\n"
                "   te_frag_texture_position = te_texture_position;\n"
                "}"
        };

        std::string fragment = {
                    "#version 330 core\n"
                    "\n"
                    "in vec3 te_frag_normal, te_frag_position;\n"
                    "in vec2 te_frag_texture_position;\n"
                    "uniform vec3 te_light_position[" + LIGHTS + "];\n"
                    "uniform vec4 te_light_color[" + LIGHTS + "];\n"
                    "uniform sampler2D te_texture_slot;\n"
                    "\n"
                    "out vec4 color;\n"
                    "\n"
                    "vec3 normal = normalize(te_frag_normal);\n"
                    "\n"
                    "vec4 light;\n"
                    "\n"
                    "void main()\n"
                    "{\n"
                    "   for (int i = 0; i < " + LIGHTS + "; i++)\n"
                    "   {\n"
                    "       float distance = abs(distance(te_light_position[i], te_frag_position));"
                    "       "
                    "       vec3 lightDir = normalize(te_light_position[i] - te_frag_position);\n"
                    "       light += (te_light_color[i] * dot(normal, lightDir) * te_light_color[i].w) / distance ;\n"
                    "   }\n"
                    "   vec4 textureColor = texture(te_texture_slot, te_frag_texture_position);\n"
                    "   color = max(vec4((textureColor * light).xyz, 1.0), 0.1);\n"
                    "}"
        };

        return {vertex, fragment};
    }
}

#endif //TWIG_ENGINE_DEFAULTDIFFUSE_H
