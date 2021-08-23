#include "indexBuffer.hpp"

#include "glad/glad.h"
#include "error.hpp"

indexBuffer::indexBuffer(const unsigned int* data, unsigned int count) :
    m_count(count)
{
    glCall(glGenBuffers(1, &m_rendererID));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(unsigned int) , data, GL_STATIC_DRAW));
}

indexBuffer::~indexBuffer()
{
    glCall(glDeleteBuffers(1, &m_rendererID));
}

void indexBuffer::bind() const
{
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
}
void indexBuffer::unbind() const
{
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}