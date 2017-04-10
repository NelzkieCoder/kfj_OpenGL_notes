//
// Created by fangjun on 17/09/16.
//

//! @file 1_hello_world.cpp
//! It demostrates how to create a window with GLFW.
//! When the user presses Esc, the window is closed automatically
//! and the program exits.

#include "common.hpp"

//! Display a window.
//! This is my first program in OpenGL, which just displays a window!
//! Although it does nothing special, it is a big step forward!
//!
//! Press Esc to exit the program.
//! return 0 on success
int hello_world()
{
    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
    GLFWwindow *window;

    create_context(&window);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
