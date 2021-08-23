#pragma once

#include <glad/glad.h>

#include <string>


class shader
{
public:
    shader(std::string vertexShaderPath, std::string fragmentShaderPath);
    ~shader();

    unsigned int getProgramID() {return m_program_id; }

    void printVertexShader();
    void printFragmentShader();

    void reload();

private:
    unsigned int readFile();

    unsigned int compileShader(unsigned int type, std::string source);
    unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);

    std::string m_fragmentShaderPath;
    std::string m_vertexShaderPath;

    std::string m_vertexShaderSource;
    std::string m_fragmentShaderSource;

    unsigned int m_program_id;

};