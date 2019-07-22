//
// Created by max on 19/07/19.
//

#include <GL/glew.h>
#include <fstream>

#include "Video/GL/GL_Shader.h"
#include "Debug.h"

using namespace TE;

GL_Shader::GL_Shader(const char *vertexSrc, const char *fragmentSrc) {
    BuildShader(vertexSrc, fragmentSrc);
}

void GL_Shader::BuildShader(const char *vertexSrc, const char *fragmentSrc)
{
    ID = glCreateProgram();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER), fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
    glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);

    GLint vertexStatus, fragmentStatus, programStatus;

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexStatus);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentStatus);

    if (vertexStatus == GL_FALSE)
    {
        Debug::Log("Failed to compile vertex shader", Debug::Severity::Error);
    }
    if (fragmentStatus == GL_FALSE)
    {
        Debug::Log("Failed to compile fragment shader", Debug::Severity::Error);
    }

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    glLinkProgram(ID);
    glValidateProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &programStatus);

    if (programStatus == GL_FALSE)
    {
        Debug::Log("Failed to compile shader program", Debug::Severity::Error);
    }

    Debug::Log("Generated OpenGL shader with ID: " + std::to_string(ID));
}

GL_Shader::~GL_Shader() {
    glDeleteProgram(ID);
}

void GL_Shader::Bind() {
    Debug::Log("Binding shader ID: " + std::to_string(ID));
    glUseProgram(ID);
}

void GL_Shader::Unbind() {
    //Todo Implement default shader
    glUseProgram(0);
}
