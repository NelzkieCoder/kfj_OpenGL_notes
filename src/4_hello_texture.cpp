//
// Created by fangjun on 28/09/16.
//

// use of texture

/*
 *
 * For the explanation to the code, refer to http://learnopengl.com/#!Getting-started/Textures
 * Refer to http://learnopengl.com/code_viewer.php?code=getting-started/textures_combined for the original source code
 *
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


// https://github.com/smibarber/libSOIL
#include "SOIL.h"

#include "Shader.hpp"

// texture image 1
const static std::string kImg1 = "pic/container.jpg";

// texture image 2
const static std::string kImg2 = "pic/awesomeface.png";

// Window dimensions
const static GLuint kWidth = 800, kHeight = 600;

// vertex shader source filename
const static std::string kVertexShaderFilename = "src/shaders/4_hello_texture_vertex_shader.txt";

// fragment shader source filename
const static std::string kFragShaderFilename = "src/shaders/4_hello_texture_fragment_shader.txt";



std::string load_shader_from_file(const std::string filename);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


int hello_texture()
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


    // load shaders
    Shader shader;
    shader.setVertexShaderFilename(kVertexShaderFilename);
    shader.setFragmentShaderFilename(kFragShaderFilename);
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
    unsigned char* img1 = SOIL_load_image(kImg1.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    std::cout << "(" << width << ", " << height << ")" << std::endl;
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

    // TODO: how is the image stored in the memory ???
    // e.g: how are RGB values store?
    unsigned char* img2 = SOIL_load_image(kImg2.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    std::cout << "(" << width << ", " << height << ")" << std::endl;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img2);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(img2);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);



    GLfloat vertices[] = {
            // points           color               texture coordinate
            0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,         // top right
            0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,         // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   0.0f, 0.0f,         // bottom left
            -0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f,         // top left
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
            3, // number of component per vertex attribute. Each coordinate contains 3 component
            GL_FLOAT, // data type of each component
            GL_FALSE, // need to be normalized ?
            8*sizeof(GLfloat),  // stride, 0 -> compact, OpenGL will compute it. non-zero --> number of bytes between two consecutive vertices
            nullptr);   // offset

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
            1, // index, which attribute
            3, // number of component per vertex attribute. Each coordinate contains 3 component
            GL_FLOAT, // data type of each component
            GL_FALSE, // need to be normalized ?
            8*sizeof(GLfloat),  // stride, 0 -> compact, OpenGL will compute it. non-zero --> number of bytes between two consecutive vertices
            reinterpret_cast<GLvoid*>(3*sizeof(GLfloat)));   // offset

    glEnableVertexAttribArray(1);

    glVertexAttribPointer(
            2, // index, which attribute
            2, // number of component per vertex attribute. Each coordinate contains 3 component
            GL_FLOAT, // data type of each component
            GL_FALSE, // need to be normalized ?
            8*sizeof(GLfloat),  // stride, 0 -> compact, OpenGL will compute it. non-zero --> number of bytes between two consecutive vertices
            reinterpret_cast<GLvoid*>(6*sizeof(GLfloat)));   // offset

    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // clear the color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.useProgram();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glUniform1i(glGetUniformLocation(shader.getProgram(), "myTexture1"), 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glUniform1i(glGetUniformLocation(shader.getProgram(), "myTexture2"), 1);


        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        //glBindTexture(GL_TEXTURE_2D, 0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    return 0;
}
