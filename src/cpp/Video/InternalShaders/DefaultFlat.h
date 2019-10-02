//
// Created by max on 02/10/19.
//

#ifndef TWIG_ENGINE_DEFAULTFLAT_H
#define TWIG_ENGINE_DEFAULTFLAT_H

#include "Global.h"

namespace TE {
    std::pair<std::string, std::string> s_DefaultFlat()
    {
        std::string vertex = {
                R"(
                #version 330 core
                
                layout (location = 0) in vec3 te_position;
                layout (location = 1) in vec2 te_texture_position;
                
                uniform mat4 te_projection, te_view, te_model;

                out vec2 te_frag_texture_position;
                
                void main()
                {
                   vec4 pos = (te_projection * te_view * te_model) * vec4(te_position, 1.0);
                   gl_Position = pos;
                   te_frag_texture_position = te_texture_position;
                }
                )"
        };

        std::string fragment = {
                R"(
                #version 330 core
                in vec2 te_frag_texture_position;
                uniform sampler2D te_texture_slot;

                out vec4 color;

                void main()
                {
                    color = texture(te_texture_slot, te_frag_texture_position);
                }
                )"

        };

        return {vertex, fragment};
    }
}

#endif //TWIG_ENGINE_DEFAULTFLAT_H
