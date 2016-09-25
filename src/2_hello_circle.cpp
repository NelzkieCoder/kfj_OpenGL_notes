//
// Created by fangjun on 25/09/16.
//

// draw a cicle with OpenGL core profile

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
#include <vector>
#include <fstream>
#include <math.h>

#include "Shader.hpp"

const static GLfloat kPi = 3.1415926f;

// Window dimensions
// the aspect ratio should be 1:1 for a circle !
const static GLuint kWidth = 800, kHeight = 800;

// vertex shader source filename
const static std::string kVertexShaderFilename = "src/shaders/2_hello_triangle_vertex_shader.txt";

// fragment shader source filename
const static std::string kFragShaderFilename = "src/shaders/2_hello_triangle_fragment_shader.txt";




std::string loadShaderFromFile(const std::string filename);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


int hello_circle()
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
    shader.setFragShaderFilename(kFragShaderFilename);
    shader.linkProgram();


    // radius should be in the range (0, 1]
    GLfloat radius = 0.8f;
    GLint num_points = 100;
    std::vector<GLfloat> points;
    GLfloat tmp = 2 * kPi / num_points;

    for (int i = 0; i < num_points; ++i) {
        GLfloat x = radius * cosf(tmp * i);
        GLfloat y = radius * sinf(tmp * i);
        points.push_back(x);
        points.push_back(y);
        points.push_back(0.0f);
    }

    GLuint vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // set the current vertex array.
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER ,vbo);
    glBufferData(GL_ARRAY_BUFFER, points.size()*sizeof(GLfloat), points.data(), GL_STATIC_DRAW);


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


    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // clear the color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw the circle (draw a line between two neighboring points)
        shader.useProgram();
        glBindVertexArray(vao);
        glDrawArrays(
                GL_LINE_LOOP, // primitives
                0, // starting index
                num_points // number of indices
        );

        glBindVertexArray(0); // reset;

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    glfwTerminate();

    return 0;
}