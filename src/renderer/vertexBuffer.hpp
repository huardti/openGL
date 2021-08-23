#pragma once

class vertexBuffer
{
public:
    vertexBuffer(const void* data, unsigned int size);
    ~vertexBuffer();

    void bind() const;
    void unbind() const;

private:
    unsigned int m_rendererID;
};