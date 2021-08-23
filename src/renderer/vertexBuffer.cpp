#include "vertexBuffer.hpp"

#include "glad/glad.h"
#include "error.hpp"

vertexBuffer::vertexBuffer(const void* data, unsigned int size)
{
    glCall(glGenBuffers(1, &m_rendererID));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
    glCall(glBufferData(GL_ARRAY_BUFFER, size , data, GL_STATIC_DRAW));
}

vertexBuffer::~vertexBuffer()
{
    glCall(glDeleteBuffers(1, &m_rendererID));
}

void vertexBuffer::bind() const
{
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}
void vertexBuffer::unbind() const
{
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}