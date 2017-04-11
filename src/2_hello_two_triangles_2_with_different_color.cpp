//
// Created by fangjun on 25/09/16.
//

#include "common.hpp"
#include "shader.hpp"


//! Draw to triangles with different colors
int hello_two_triangles_2_with_different_color()
{
    std::string vertex_shader_Filename = g_shader_path + "/src/shaders/2_hello_triangle_vertex_shader.txt";
    std::string fragment_shader_filename1 = g_shader_path + "/src/shaders/2_hello_triangle_fragment_shader.txt";
    std::string fragment_shader_filename2 = g_shader_path + "/src/shaders/2_hello_triangle_fragment_shader_yellow.txt";

    GLFWwindow *window;
    create_context(&window);

    Shader shader1;
    shader1.setVertexShaderFilename(vertex_shader_Filename);
    shader1.setFragmentShaderFilename(fragment_shader_filename1);
    shader1.linkProgram();

    Shader shader2;
    shader2.setVertexShaderFilename(vertex_shader_Filename);
    shader2.setFragmentShaderFilename(fragment_shader_filename2);
    shader2.linkProgram();

    // set the coordinate of the triangle vertices
    GLfloat first_triangle[] = {
            -0.9f, 0.0f, 0.0f, // left vertex
            -0.1f, 0.0f, 0.0f,  // right vertex
            -0.1f, 0.5f, 0.0f,   // top vertex
    };

    GLfloat second_triangle[] = {
            0.1f, 0.0f, 0.0f,
            0.5f, 0.0f, 0.0f,
            0.5f, -0.9f, 0.0f,
    };

    GLuint vbo[2], vao[2];
    glGenVertexArrays(2, vao);
    glGenBuffers(2, vbo);

    // set the current vertex array.
    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ARRAY_BUFFER ,vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(first_triangle), first_triangle, GL_STATIC_DRAW);

    glVertexAttribPointer(
            0, // index, which attribute
            3, // number of component per vertex attribute. Each coordinate contains 3 component
            GL_FLOAT, // data type of each component
            GL_FALSE, // need to be normalized ?
            0,  // stride, 0 -> compact, OpenGL will compute it. non-zero --> number of bytes between two consecutive vertices
            nullptr);   // offset

    glEnableVertexAttribArray(0);

    // second triangle

    glBindVertexArray(vao[1]);

    glBindBuffer(GL_ARRAY_BUFFER ,vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(second_triangle), second_triangle, GL_STATIC_DRAW);

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
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw the triangle
        shader1.useProgram();
        glBindVertexArray(vao[0]);

        // first triangle
        glDrawArrays(
                GL_TRIANGLES, // primitives
                0, // starting index
                3 // number of indices
        );

        shader2.useProgram();
        glBindVertexArray(vao[1]);
        // second triangle
        glDrawArrays(
                GL_TRIANGLES, // primitives
                0, // starting index
                3 // number of indices
        );

        glBindVertexArray(0); // reset;

        glfwSwapBuffers(window);
    }

    glDeleteBuffers(2, vbo);
    glDeleteVertexArrays(2, vao);

    glfwTerminate();

    return 0;
}
