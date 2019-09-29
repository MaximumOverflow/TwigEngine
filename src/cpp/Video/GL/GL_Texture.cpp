//
// Created by max on 28/07/19.
//

#include "Video/GL/GL_Texture.h"
#include "External/stb/stb_image.h"
#include "Debug.h"

#include <GL/glew.h>
#include <Video/GL/GL_Texture.h>
#include <cstring>

TE::GL_Texture::GL_Texture() {
    Debug::Log("Creating OpenGL Texture...");
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    Debug::Log("OpenGL Texture successfully created");
}

TE::GL_Texture::GL_Texture(const std::string path, bool retainBuffer) {
    Debug::Log("Creating OpenGL Texture...");

    stbi_set_flip_vertically_on_load(true);
    buffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);

    glCreateTextures(GL_TEXTURE_2D, 1, &ID);
    glTextureStorage2D(ID, 1, GL_RGBA8, (unsigned int) width, (unsigned int) height);

    glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTextureSubImage2D(ID, 0, 0, 0, (unsigned int) width, (unsigned int) height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

    if(!retainBuffer)
    {
        stbi_image_free(buffer);
        buffer = nullptr;
    }

    Debug::Log("OpenGL Texture successfully created");
}

TE::GL_Texture::~GL_Texture() {
    glDeleteTextures(1, &ID);

    if (buffer != nullptr)
        stbi_image_free(buffer);
}

void TE::GL_Texture::Bind(unsigned int slot) {
    if (slot > 31)
    {
        TE::Debug::Log("Invalid OpenGL texture slot. Reverting to slot 0...", Debug::Severity::Warning);
        slot = 0;
    }
    glBindTextureUnit(slot, ID);
    this->slot = slot;
}

void TE::GL_Texture::Unbind() {
    glBindTextureUnit(slot, 0);
}

const unsigned int TE::GL_Texture::GetID() const {
    return ID;
}

TE::GL_Texture::GL_Texture(const unsigned char* buffer, int width, int height, int bpp) {
    this->width = width;
    this->height = height;
    this->bpp = bpp;

    Debug::Log("Creating OpenGL Texture...");
    glCreateTextures(GL_TEXTURE_2D, 1, &ID);
    glTextureStorage2D(ID, 1, GL_RGBA8, (unsigned int) width, (unsigned int) height);

    glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTextureSubImage2D(ID, 0, 0, 0, (unsigned int) width, (unsigned int) height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

    Debug::Log("OpenGL Texture successfully created");
}
