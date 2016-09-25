//
// Created by fangjun on 25/09/16.
//

//  draw two triangles


/*
 *
 * For the complete source code, refer to http://learnopengl.com/code_viewer.php?code=getting-started/hellotriangle
 * For the explanation to the code, refer to http://learnopengl.com/#!Getting-started/Hello-Triangle
 */

/**
 *
 * Note: include GLEW before GLFW !!!
 *
 * #define GLEW_STATIC  // to link statically
 */


// GLEW
// #define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <iostream>

#include <fstream>

#include "Shader.hpp"

// Window dimensions
const static GLuint WIDTH = 800, HEIGHT = 600;

// vertex shader source filename
const static std::string VERTEX_SHADER_FILENAME = "src/shaders/2_hello_triangle_vertex_shader.txt";

// fragment shader source filename
const static std::string FRAGMENT_SHADER_FILENAME = "src/shaders/2_hello_triangle_fragment_shader.txt";




std::string loadShaderFromFile(const std::string filename);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


int hello_two_triangles()
{
    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
    glfwInit();

    // refer to http://www.glfw.org/docs/latest/window.html#window_hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    // initialize GLEW

    // true -> to use modern techniques
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // set viewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    // map normalized device coordinates
    // [-1, 1] --> [0, 800]
    //             [0, 600]
    glViewport(0, 0, width, height);

    Shader shader;
    shader.setVertexShaderFilename(VERTEX_SHADER_FILENAME);
    shader.setFragShaderFilename(FRAGMENT_SHADER_FILENAME);
    shader.linkProgram();


    // set the coordinate of the triangle vertices
    GLfloat vertices[] = {
            -0.5f, 0.0f, 0.0f, // left vertex
            -0.1f, 0.0f, 0.0f,  // right vertex
            -0.1f, 0.5f, 0.0f,   // top vertex
            // second triangle
            0.1f, 0.0f, 0.0f,
            0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f,
    };

    GLuint vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // set the current vertex array.
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER ,vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(
            0, // index, which attribute
            3, // number of component per vertex attribute. Each coordinate contains 3 component
            GL_FLOAT, // data type of each component
            GL_FALSE, // need to be normalized ?
            0,  // stride, 0 -> compact, OpenGL will compute it. non-zero --> number of byte between two consecutive vertices
            nullptr);   // offset

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);   // reset
    glBindVertexArray(0);

    // comment out this statement to fill the triangle
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // clear the color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw the triangle
        shader.useProgram();
        glBindVertexArray(vao);

        // either of the following two drawing methods are fine

#if true
        // draw two triangles
        glDrawArrays(
                GL_TRIANGLES, // primitives
                0, // starting index
                6 // number of indices
        );
#else

        // first triangle
        glDrawArrays(
                GL_TRIANGLES, // primitives
                0, // starting index
                3 // number of indices
        );

        // second triangle
        glDrawArrays(
                GL_TRIANGLES, // primitives
                3, // starting index
                3 // number of indices
        );
#endif
        glBindVertexArray(0); // reset;

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    glfwTerminate();

    return 0;
}