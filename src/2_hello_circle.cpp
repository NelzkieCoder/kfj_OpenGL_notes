//
// Created by fangjun on 25/09/16.
//

#include <math.h>
#include <vector>

#include "common.hpp"
#include "shader.hpp"

//! Draw a circle.
//! It first samples the circle, then draw lines between the
//! sampled points.
int hello_circle()
{
    std::string vertex_shader_filename = g_shader_path + "/src/shaders/2_hello_triangle_vertex_shader.txt";
    std::string fragment_shader_filename = g_shader_path + "/src/shaders/2_hello_triangle_fragment_shader.txt";

    GLFWwindow *window;
    create_context(&window, 500, 500); // a square window to display the circle

    Shader shader;
    shader.setVertexShaderFilename(vertex_shader_filename);
    shader.setFragmentShaderFilename(fragment_shader_filename);
    shader.linkProgram();

    const GLfloat pi = 3.1415926f;
    GLfloat radius = 0.8f;  // radius should be in the range (0, 1]
    size_t num_points = 300; // number of points to sample the circle
    std::vector<GLfloat> points(num_points*3);
    GLfloat tmp = 2 * pi / num_points;

    for (size_t i = 0; i < num_points; i++) {
        GLfloat x = radius * cosf(tmp * i);
        GLfloat y = radius * sinf(tmp * i);
        points[3*i]   = x;
        points[3*i+1] = y;
        points[3*i+2] = 0.0f;
    }

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER ,vbo);
    glBufferData(GL_ARRAY_BUFFER, points.size()*sizeof(GLfloat), points.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(
            0, // index, which attribute
            3, // number of component per vertex attribute. Each coordinate contains 3 component
            GL_FLOAT, // data type of each component
            GL_FALSE, // need to be normalized ?
            0,  // stride, 0 -> compact, OpenGL will compute it. non-zero --> number of bytes between two consecutive vertices
            nullptr);   // offset

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);   // reset
    glBindVertexArray(0);

    shader.useProgram();
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // clear the color buffer
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw the circle (GL_LINE_LOOP, draw a line between two neighboring points)
        glBindVertexArray(vao);
        glDrawArrays(
                GL_LINE_LOOP, // primitives
                0, // starting index
                (GLsizei)num_points // number of indices
        );
        glBindVertexArray(0); // reset;

        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glfwTerminate();

    return 0;
}
