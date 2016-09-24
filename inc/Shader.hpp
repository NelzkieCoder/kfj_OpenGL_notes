//
// Created by fangjun on 24/09/16.
//

#ifndef KFJ_OPENGL_NOTES_SHADER_HPP
#define KFJ_OPENGL_NOTES_SHADER_HPP

// GLEW
// #define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <iostream>

#include <fstream>

class Shader {

public:
    Shader();

    /**
     * set the filename for vertex shader
     */
    void setVertexShaderFilename(const std::string& f_filename);

    /**
     * set the filename for fragment shader
     */
    void setFragShaderFilename(const std::string& f_filename);

    /**
     * compile shaders and link them into a program
     */
    void linkProgram();

    /**
     * Set the program as the current program used by OpenGL
     */
    void useProgram() const;

private:
    GLuint m_program;
    /**
     * contains source code for vertex shader
     */
    std::string m_vertexCode;

    /**
     * filename for vertex shader
     */
    std::string m_vertexFilename;

    /**
     * contains source code for fragment shader
     */
    std::string m_fragCode;

    /**
     * filename for fragment shader
     */
    std::string m_fragFilename;
};


#endif //KFJ_OPENGL_NOTES_SHADER_HPP
