#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
  

class Shader {
public:
    //program id
    unsigned int ID;

    //constructor reads / builds shader
    Shader(const char* vertexPath, const char* fragmentPath);
    //activate shader
    void use();
    
    //util functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

#endif
