//
// Created by fangjun on 17/09/16.
//

#include "common.hpp"

//! @brief Display a window.
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
