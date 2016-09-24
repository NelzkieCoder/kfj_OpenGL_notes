//
// Created by fangjun on 24/09/16.
//

// GLEW
// #define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <iostream>

#include <fstream>


/**
 *
 * action:
 *      GLFW_RELEASE
 *      GLFW_PRESS
 */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    std::cout << key << std::endl;

    // When a user presses the escape key, we set the WindowShouldClose property to true,
    // closing the application
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

std::string loadShaderFromFile(const std::string filename)
{
    std::ifstream in (filename);
    if(in.is_open() == false)
    {
        std::cerr << "Cannot open file " << filename << std::endl;
        exit(-1);
    }
    std::string result (
            (std::istreambuf_iterator<char> (in)),
            std::istreambuf_iterator<char> ());
    return result;
}
