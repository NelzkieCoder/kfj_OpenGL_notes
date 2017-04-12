#include "common.hpp"
#include "shader.hpp"

// https://github.com/smibarber/libSOIL
#include "SOIL.h"

//! It demonstrates using different textures for different objects.
//! @sa hello_texture
//! @image html pic/exercises/texture-02.png "Output"
int texture_exercise()
{
    std::string img1_path = g_pic_path + "/pic/container.jpg";  // texture image 1
    std::string img2_path = g_pic_path + "/pic/awesomeface.png"; // texture image 2

    std::string vertex_source =
    "#version 330 core" "\n"
    "layout (location = 0) in vec3 pos;"  "\n"
    "layout (location = 1) in vec2 in_tex_coord;"  "\n"
    "out vec2 tex_coord;"  "\n"
    "void main()" "\n"
    "{" "\n"
    "   gl_Position = vec4(pos, 1.0);" "\n"
    "   tex_coord = vec2(in_tex_coord.x, 1-in_tex_coord.y);" "\n" // flip the texture image
    "}"  "\n"
    ;

    std::string fragment_source =
    "#version 330 core"  "\n"
    "in vec2 tex_coord;" "\n"
    "out vec4 color;"  "\n"
    "uniform sampler2D myTexture;" "\n"
    "void main()"   "\n"
    "{"   "\n"
    "   color = texture(myTexture, tex_coord);"  "\n"
    "}"
    ;

    GLFWwindow *window;
    create_context(&window);

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

    int width, height;
    unsigned char* img1 = SOIL_load_image(img1_path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img1);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(img1);

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

    glBindTexture(GL_TEXTURE_2D, 0);

    GLfloat vertices[] = {
        // first triangle
        -0.5f, 0, // left, 0
        -0.1f, 0, // right, 1
        -0.1f, 0.5f, //top , 2
        // second triangle
        0.1f, 0, // left, 3
        0.5f, 0, // right, 4
        0.1f, 0.5f, // top, 5
    };

    GLfloat texture_coordinates[] = {
        // texture coordinate of the first triangle
        0, 0,
        1, 0,
        0.5f, 1,
        // texture coordinate of the second triangle
        0, 0,
        1, 0,
        0.5f, 1
    };

    GLuint vao, vbo[2];
    glGenVertexArrays(1, &vao);
    glGenBuffers(2, vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texture_coordinates), texture_coordinates, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(
            0, // index, which attribute
            2, // number of component per vertex attribute. Each coordinate contains 3 component
            GL_FLOAT, // data type of each component
            GL_FALSE, // need to be normalized ?
            0,  // stride
            nullptr);   // offset
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(
            1, // index, which attribute
            2, // number of component per vertex attribute. Each coordinate contains 3 component
            GL_FLOAT, // data type of each component
            GL_FALSE, // need to be normalized ?
            0,  // stride
            nullptr);   // offset

    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    shader.useProgram();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // clear the color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glUniform1i(glGetUniformLocation(shader.getProgram(), "myTexture"), 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUniform1i(glGetUniformLocation(shader.getProgram(), "myTexture"), 1);
        glDrawArrays(GL_TRIANGLES, 3, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(2, vbo);

    return 0;
}
