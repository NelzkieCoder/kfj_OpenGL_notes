//
// Created by fangjun on 24/09/16.
//

#include "Shader.hpp"

std::string loadShaderFromFile(const std::string filename);

Shader::Shader()
    : m_program(0)
{

}

void Shader::setVertexShaderFilename(const std::string &f_filename)
{
    m_vertexFilename = f_filename;
}

void Shader::setFragShaderFilename(const std::string &f_filename)
{
    m_fragFilename = f_filename;
}

void Shader::linkProgram()
{
    m_vertexCode = loadShaderFromFile(m_vertexFilename);
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const char *p = m_vertexCode.c_str();
    glShaderSource(vertexShader, 1, &p, nullptr);
    glCompileShader(vertexShader);

    GLint success = GL_FALSE;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        GLint len;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &len);
        std::string logInfo(len - 1, 0); // as null terminator is contained in the length
        glGetShaderInfoLog(vertexShader, len, nullptr, &logInfo[0]);
        std::cout << "compile info for vertex shader : " << std::endl
        << logInfo << std::endl;
        exit(-1);
    }

    m_fragCode = loadShaderFromFile(m_fragFilename);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    p = m_fragCode.c_str();
    glShaderSource(fragShader, 1, &p, nullptr);
    glCompileShader(fragShader);

    success = GL_FALSE;
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        GLint len;
        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &len);
        std::string logInfo(len - 1, 0); // as null terminator is contained in the length
        glGetShaderInfoLog(fragShader, len, nullptr, &logInfo[0]);
        std::cout << "compile info for fragment shader : " << std::endl
        << logInfo << std::endl;
        exit(-1);
    }

    // link shaders into a program
    m_program = glCreateProgram();
    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragShader);
    glLinkProgram(m_program);

    success = GL_FALSE;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if(!success)
    {
        GLint len;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &len);
        std::string logInfo(len - 1, 0); // as null terminator is contained in the length
        glGetProgramInfoLog(m_program, len, nullptr, &logInfo[0]);
        std::cout << "link info for program : " << std::endl
        << logInfo << std::endl;
        exit(-1);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
}

void Shader::useProgram() const
{
    glUseProgram(m_program);
}