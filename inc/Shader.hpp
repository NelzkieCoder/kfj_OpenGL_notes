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

    ~Shader();


    //! Set the filename for vertex shader
    //! @param f_filename [in] Name of the vertex shader source file
    void setVertexShaderFilename(const std::string& f_filename);

    //! Set the vertex shader source code.
    //! @param f_vertex_code [in] The source code of the vertex shader.
    void setVertexShaderSource(const std::string& f_vertex_code);

    //! set the filename for fragment shader
    //! @param f_filename [in] Name of the fragment shader source file
    void setFragmentShaderFilename(const std::string& f_filename);

    //! Set the fragment shader source code
    //! @param f_fragment_code [in] The source code of the fragment shader.
    void setFragmentShaderSource(const std::string& f_fragment_code);

    /**
     * compile shaders and link them into a program
     */
    void linkProgram();

    /**
     * Set the program as the current program used by OpenGL
     */
    void useProgram() const;

    GLuint getProgram() const {return m_program;}

private:
    GLuint m_program; //!< the program object linked from the vertex and fragment shader
    std::string m_vertex_code;  //!< contains source code for vertex shader
    std::string m_vertex_filename;  //!< filename for vertex shader
    std::string m_fragment_code;  //!< contains source code for fragment shader
    std::string m_fragment_filename; //!< filename for fragment shader
};


#endif //KFJ_OPENGL_NOTES_SHADER_HPP
