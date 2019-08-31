//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_MACROS_H
#define TWIG_ENGINE_MACROS_H

#include "Video/FrameBufferObject.h"
#include "Video/VertexArrayObject.h"
#include "Video/VertexBufferObject.h"
#include "Video/IndexBufferObject.h"
#include "Video/Shader.h"
#include "Video/Texture.h"
#include "Objects/Mesh.h"

namespace TE {
    typedef std::shared_ptr<VertexArrayObject> pVertexArrayObject;
    typedef std::shared_ptr<VertexBufferObject> pVertexBufferObject;
    typedef std::shared_ptr<IndexBufferObject> pIndexBufferObject;
    typedef std::shared_ptr<FrameBufferObject> pFrameBufferObject;

    typedef std::shared_ptr<Shader> pShader;
    typedef std::shared_ptr<Mesh> pMesh;
    typedef std::shared_ptr<Texture> pTexture;
}

#define TE_BIND_CALLBACK(f) std::bind(&f, this, std::placeholders::_1)

#endif //TWIG_ENGINE_MACROS_H
