#include "shader.hpp"

#include <iostream>
#include <fstream>

#include "error.hpp"

shader::shader(std::string vertexShaderPath, std::string fragmentShaderPath) :
        m_vertexShaderPath(vertexShaderPath),
        m_fragmentShaderPath(fragmentShaderPath)
{
    reload();
}

shader::~shader()
{
    glCall(glDeleteProgram(m_program_id));
}

void shader::reload()
{
    std::ifstream vs_file(m_vertexShaderPath);
    if (!vs_file.is_open()) {
        std::cout << "can't open vertex shader located at " << m_vertexShaderPath << std::endl;
        exit(-1);
    }
    std::ifstream fs_file(m_fragmentShaderPath);
    if (!fs_file.is_open()) {
        std::cout << "can't open fragment shader located at " << m_fragmentShaderPath << std::endl;
        exit(-1);
    }

    vs_file.seekg(0, std::ios::end);
    m_vertexShaderSource.reserve(vs_file.tellg());
    vs_file.seekg(0, std::ios::beg);
    m_vertexShaderSource.assign((std::istreambuf_iterator<char>(vs_file)), std::istreambuf_iterator<char>());

    fs_file.seekg(0, std::ios::end);
    m_fragmentShaderSource.reserve(fs_file.tellg());
    fs_file.seekg(0, std::ios::beg);
    m_fragmentShaderSource.assign((std::istreambuf_iterator<char>(fs_file)), std::istreambuf_iterator<char>());

    m_program_id = createShader(m_vertexShaderSource, m_fragmentShaderSource);

    fs_file.close();
    vs_file.close();
}

void shader::bind(){
    glCall(glUseProgram(m_program_id));
}

void shader::unbind(){
    glCall(glUseProgram(0));
}

unsigned int shader::compileShader(unsigned int type, std::string source)
{
    unsigned id = glCreateShader(type);
    const char* src = source.c_str();
    glCall(glShaderSource(id, 1, &src, nullptr));
    glCall(glCompileShader(id));

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int log_length = 0;
        glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length));
        char * message = new char[log_length];
        glCall(glGetShaderInfoLog(id, log_length, &log_length, message));
        std::cout << "fail to compile " << ((type == GL_FRAGMENT_SHADER)? "fragment" : "vertex") << " shader! (" << ((type == GL_FRAGMENT_SHADER)? m_fragmentShaderPath : m_vertexShaderPath) << ")" << std::endl;
        std::cout << message << std::endl;
        delete [] message;
        glCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int  programme = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    if(vs == 0 || fs == 0){
        exit(-1);
    }

    glCall(glAttachShader(programme, vs));
    glCall(glAttachShader(programme, fs));

    glCall(glLinkProgram(programme));
    glCall(glValidateProgram(programme));

    glCall(glDeleteShader(vs));
    glCall(glDeleteShader(fs));

    return programme;
}

void shader::printVertexShader()
{
    std::cout << "vertex shader located at : "  << m_vertexShaderPath << std::endl;
    std::cout << m_vertexShaderSource << std::endl;
}

void shader::printFragmentShader()
{
    std::cout << "fragment shader located at : "  << m_fragmentShaderPath << std::endl;
    std::cout << m_fragmentShaderSource << std::endl;
}