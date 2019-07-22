//
// Created by max on 20/07/19.
//

#ifndef TWIG_ENGINE_GL_INDEXBUFFEROBJECT_H
#define TWIG_ENGINE_GL_INDEXBUFFEROBJECT_H

#include "Video/IndexBufferObject.h"

class GL_IndexBufferObject : public TE::IndexBufferObject{
private:
    unsigned int ID;
    unsigned int elements;
public:
    ~GL_IndexBufferObject() override;
    GL_IndexBufferObject();

    void Bind() override;
    void Unbind() override;
    unsigned long GetRendererID() override;

    void SetData(uint32_t elements, unsigned int*data) override;

    unsigned int GetElementCount() override;
};


#endif //TWIG_ENGINE_GL_INDEXBUFFEROBJECT_H
