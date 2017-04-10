//
// Created by fangjun on 24/09/16.
//
#include <iostream>
#include <fstream>

#include "common.hpp"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // close the window when Esc is pressed
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

std::string load_shader_from_file(const std::string& filename)
{
    std::ifstream in (filename);
    if(in.is_open() == false)
    {
        std::cerr << "Cannot open file " << filename << std::endl;
        exit(-1);
    }
    std::string result (
            (std::istreambuf_iterator<char> (in)),
            std::istreambuf_iterator<char> ()
          );
    return result;
}
