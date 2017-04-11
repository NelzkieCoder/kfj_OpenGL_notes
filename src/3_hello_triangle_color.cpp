//
// Created by fangjun on 25/09/16.
//

// draw a triangle and change its color via vertex attributes.

/*
 *
 * For the explanation to the code, refer to http://learnopengl.com/#!Getting-started/Shaders
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
#include <math.h>
#include <fstream>

#include "Shader.hpp"

// Window dimensions
const static GLuint kWidth = 800, kHeight = 600;

// vertex shader source filename
const static std::string kVertexShaderFilename = "src/shaders/3_hello_triangle_vertex_shader_color.txt";

// fragment shader source filename
const static std::string kFragShaderFilename = "src/shaders/3_hello_triangle_fragment_shader_color.txt";


std::string load_shader_from_file(const std::string filename);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


int hello_triangle_color()
{
    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
    glfwInit();

    // refer to http://www.glfw.org/docs/latest/window.html#window_hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(kWidth, kHeight, "LearnOpenGL", nullptr, nullptr);
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
    shader.setVertexShaderFilename(kVertexShaderFilename);
    shader.setFragmentShaderFilename(kFragShaderFilename);
    shader.linkProgram();


    // set the coordinate of the triangle vertices
    GLfloat vertices[] = {
            // vertex           color
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // left vertex
            0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // right vertex
            0.0f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   // top vertex
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
            6*sizeof(GLfloat),  // stride, 0 -> compact, OpenGL will compute it. non-zero --> number of bytes between two consecutive vertices
            nullptr);   // offset

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
            1, // index, which attribute
            3, // number of component per vertex attribute. Each coordinate contains 3 component
            GL_FLOAT, // data type of each component
            GL_FALSE, // need to be normalized ?
            6*sizeof(GLfloat),  // stride, 0 -> compact, OpenGL will compute it. non-zero --> number of bytes between two consecutive vertices
            reinterpret_cast<GLvoid*>(3*sizeof(GLfloat)));   // offset

    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);   // reset
    glBindVertexArray(0);


    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // clear the color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw the triangle
        shader.useProgram();

        glBindVertexArray(vao);
        glDrawArrays(
                GL_TRIANGLES, // primitives
                0, // starting index
                3 // number of indices
        );

        glBindVertexArray(0); // reset;

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    glfwTerminate();

    return 0;
}
