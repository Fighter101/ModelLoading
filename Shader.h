//
// Created by madara on 01/12/16.
//

#ifndef LIGHTING_SHADER_H
#define LIGHTING_SHADER_H
#include "Includes.h"

class Shader {
public:
    // The program ID
    GLuint Program;
    // Constructor reads and builds the shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // Use the program
    void Use();

};


#endif //LIGHTING_SHADER_H
