#pragma once

#include <GL/glew.h>

#include "../AliveLibCommon/Types.hpp"
#include "GLShader.hpp"

class GLShaderProgram final
{
public:
    GLShaderProgram(GLShader& vertexShader, GLShader& fragmentShader);
    ~GLShaderProgram();

    void Uniform1i(const char_type* uniform, GLint x);
    void Uniform1iv(const char_type* uniform, GLsizei count, const GLint* data);
    void UniformVec2(const char_type* uniform, GLfloat x, GLfloat y);
    void UniformVec3(const char_type* uniform, GLfloat x, GLfloat y, GLfloat z);
    void UniformVec4(const char_type* uniform, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void Use();

private:
    GLuint mGLId;

    GLuint GetUniformLocation(const char_type* uniform);
};
