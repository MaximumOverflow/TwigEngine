//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_MACROS_H
#define TWIG_ENGINE_MACROS_H

#define TE_pVertexArrayObject std::shared_ptr<TE::VertexArrayObject>
#define TE_pVertexBufferObject std::shared_ptr<TE::VertexBufferObject>
#define TE_pIndexBufferObject std::shared_ptr<TE::IndexBufferObject>
#define TE_pShader std::shared_ptr<Shader>

#define TE_BIND_CALLBACK(f) std::bind(&f, this, std::placeholders::_1)

#endif //TWIG_ENGINE_MACROS_H
