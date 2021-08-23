#pragma once

#include <glad/glad.h>

#include <iostream>

void clear_error();
void get_error(unsigned int line, std::string funcName, std::string fileName);

#define glCall(x) clear_error();\
    x;\
    get_error(__LINE__, #x, __FILE__)
