#include "error.hpp"

void clear_error()
{
    while (glGetError() != GL_NO_ERROR);
}

void get_error(unsigned int line, std::string funcName, std::string fileName)
{
    unsigned int error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        std::cout << "[OpenGL] ERROR " << fileName << funcName << " line "  << line << ", error type : " << error << std::endl;
    }
}