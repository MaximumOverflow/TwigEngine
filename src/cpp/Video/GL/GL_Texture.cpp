//
// Created by max on 28/07/19.
//

#include "Video/GL/GL_Texture.h"
#include "External/stb/stb_image.h"
#include "Debug.h"

#include <GL/glew.h>
#include <Video/GL/GL_Texture.h>

TE::GL_Texture::GL_Texture() {
    Debug::Log("Creating OpenGL Texture...");
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

TE::GL_Texture::GL_Texture(const std::string path) {
    Debug::Log("Creating OpenGL Texture...");
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    stbi_set_flip_vertically_on_load(true);
    buffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    Debug::Log("OpenGL Texture successfully created");
}

TE::GL_Texture::~GL_Texture() {
    glDeleteTextures(1, &ID);
    stbi_image_free(buffer);
}

void TE::GL_Texture::Bind(unsigned int slot) {
    if (slot > 31)
    {
        TE::Debug::Log("Invalid OpenGL texture slot. Reverting to slot 0...", Debug::Severity::Warning);
        slot = 0;
    }
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, ID);
    this->slot = slot;
}

void TE::GL_Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

const unsigned int TE::GL_Texture::GetID() const {
    return ID;
}

TE::GL_Texture::GL_Texture(const unsigned char *buffer, int width, int height, int bpp) : width{width}, height{height}, bpp{bpp} {
    Debug::Log("Creating OpenGL Texture...");
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
}
