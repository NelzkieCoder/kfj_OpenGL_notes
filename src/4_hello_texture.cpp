//
// Created by fangjun on 28/09/16.
//

#include "common.hpp"
#include "shader.hpp"

// https://github.com/smibarber/libSOIL
#include "SOIL.h"

//! blending weight for the two textures
static float alpha = 0.2f;

static void my_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // close the window when Esc is pressed
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, GL_TRUE);
    } else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
      alpha += 0.1f;
      alpha = (alpha > 1.0f) ? 1.0f : alpha;

    } else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
      alpha -= 0.1f;
      alpha = (alpha < 0.0f) ? 0.0f : alpha;
    }
}


//! Use of texture.
//!
//! Press the arrow key "up" or "down" to see the effect of texture blending.
//!
//! @todo how is the image loaded by SOIL stored in the memory.
//! @image html pic/exercises/texture-01.png "Output"
int hello_texture()
{
    std::string img1_path = g_pic_path + "/pic/container.jpg";  // texture image 1
    std::string img2_path = g_pic_path + "/pic/awesomeface.png"; // texture image 2

    std::string vertex_source =
    "#version 330 core" "\n"
    "layout (location = 0) in vec2 pos;"  "\n"
    "layout (location = 1) in vec2 in_tex_coord;"  "\n"
    "out vec2 tex_coord;"  "\n"
    "void main()" "\n"
    "{" "\n"
    "   gl_Position = vec4(pos, 0.0, 1.0);" "\n"
    "   tex_coord = vec2(in_tex_coord.x, 1-in_tex_coord.y);" "\n" // flip the texture image
    "}"
    ;

    std::string fragment_source =
    "#version 330 core"  "\n"
    "uniform float alpha;"
    "in vec2 tex_coord;" "\n"
    "out vec4 color;"  "\n"
    "uniform sampler2D myTexture1;" "\n"
    "uniform sampler2D myTexture2;" "\n"
    "void main()"   "\n"
    "{"   "\n" // (1-alpha)*first + alpha*second
    "   color = mix(texture(myTexture1, tex_coord), texture(myTexture2, tex_coord), alpha);"  "\n"
    "}"
    ;

    GLFWwindow *window;
    create_context(&window);
    glfwSetKeyCallback(window, my_key_callback);

    Shader shader;
    shader.setVertexShaderSource(vertex_source);
    shader.setFragmentShaderSource(fragment_source);
    shader.linkProgram();

    // texture1
    GLuint texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // TODO: how is the image stored in the memory ???
    // e.g: how are RGB values store?
    int width, height;
    unsigned char* img1 = SOIL_load_image(img1_path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img1);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(img1);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // texture2
    GLuint texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* img2 = SOIL_load_image(img2_path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img2);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(img2);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    GLfloat vertices[] = {
            // points   texture coordinate
            0.5f, 0.5f,   1.0f, 1.0f,   // top right
            0.5f, -0.5f,  1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f,   // bottom left
            -0.5f, 0.5f,  0.0f, 1.0f,   // top left
    };

    GLuint indices[] = {
            0, 1, 3,    // top right triangle
            1, 2, 3,    // top left triangle
    };

    GLuint vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(
            0, // index, which attribute
            2, // number of component per vertex attribute. Each coordinate contains 3 component
            GL_FLOAT, // data type of each component
            GL_FALSE, // need to be normalized ?
            4*sizeof(GLfloat),  // stride
            nullptr);   // offset

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
            1, // index, which attribute
            2, // number of component per vertex attribute. Each coordinate contains 3 component
            GL_FLOAT, // data type of each component
            GL_FALSE, // need to be normalized ?
            4*sizeof(GLfloat),  // stride
            reinterpret_cast<GLvoid*>(2*sizeof(GLfloat)));   // offset

    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    shader.useProgram();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glUniform1i(glGetUniformLocation(shader.getProgram(), "myTexture1"), 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glUniform1i(glGetUniformLocation(shader.getProgram(), "myTexture2"), 1);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // clear the color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUniform1f(glGetUniformLocation(shader.getProgram(), "alpha"), alpha);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    return 0;
}
