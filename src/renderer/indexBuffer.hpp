#pragma once


class indexBuffer
{
public:
    indexBuffer(const unsigned int* data, unsigned int count);
    ~indexBuffer();

    void bind() const;
    void unbind() const;

    inline unsigned int get_count() const { return m_count; }
private:
    unsigned int m_rendererID;
    unsigned int m_count;
};