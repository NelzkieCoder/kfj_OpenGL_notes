//
// Created by fangjun on 24/09/16.
//

#include "common.hpp"
#include "shader.hpp"


//! It draws two triangles with the help of `glDrawElements`, instead of using
//! `glDrawArrays` in function @ref hello_triangle.
//!
//! @sa hello_triangle
//!
//! @todo Why the statement `glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);` has to
//! be commented out, otherwise there is nothing to show?
int hello_triangle_with_element_buffer()
{
    std::string vertex_shader_filename = g_shader_path + "/src/shaders/2_hello_triangle_vertex_shader.txt";
    std::string fragment_shader_filename = g_shader_path + "/src/shaders/2_hello_triangle_fragment_shader.txt";

    GLFWwindow *window;
    create_context(&window);

    Shader shader;
    shader.setVertexShaderFilename(vertex_shader_filename);
    shader.setFragmentShaderFilename(fragment_shader_filename);
    shader.linkProgram();

    // set the coordinate of the rectangle vertices
    GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f, // 0, left bottom
            -0.5f, 0.5f, 0.0f,  // 1, left top
            0.5f, 0.5f, 0.0f,   // 2, right top
            0.5f, -0.5f, 0.0f,  // 3, right bottom
    };
    // corner index of the rectangle
    // 1 2
    // 0 3

    GLuint indices[] = {
            0,1,2,  // first triangle
            0,3,2,  // second triangle
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER ,vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(
            0, // index, which attribute
            3, // number of component per vertex attribute. Each coordinate contains 3 component
            GL_FLOAT, // data type of each component
            GL_FALSE, // need to be normalized ?
            0,  // stride, 0 -> compact, OpenGL will compute it. non-zero --> number of bytes between two consecutive vertices
            nullptr);   // offset

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);   // reset
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // TODO: why it has to be commented out ??
    glBindVertexArray(0);

    // uncomment the following state to draw wire frame (i.e., draw two triangles).
    // comment it out to fill the triangle, so that it looks like a rectangle.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    shader.useProgram();
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // clear the color buffer
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    glfwTerminate();

    return 0;
}
