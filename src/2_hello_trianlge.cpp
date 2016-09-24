//
// Created by fangjun on 17/09/16.
//

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

// Window dimensions
const static GLuint WIDTH = 800, HEIGHT = 600;

// vertex shader source filename
const static std::string VERTEX_SHADER_FILENAME = "src/shaders/2_hello_triangle_vertex_shader.txt";

// fragment shader source filename
const static std::string FRAGMENT_SHADER_FILENAME = "src/shaders/2_hello_triangle_fragment_shader.txt";




std::string loadShaderFromFile(const std::string filename);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


int hello_triangle()
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

    // load and compile vertex shader
    std::string vertexShaderSrc = loadShaderFromFile(VERTEX_SHADER_FILENAME);
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const char *p = vertexShaderSrc.c_str();
    glShaderSource(vertexShader, 1, &p, nullptr);
    glCompileShader(vertexShader);

    GLint success = GL_FALSE;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        GLint len;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &len);
        std::string logInfo(len - 1, 0); // as null terminator is contained in the length
        glGetShaderInfoLog(vertexShader, len, nullptr, &logInfo[0]);
        std::cout << "compile info for vertex shader : " << std::endl
        << logInfo << std::endl;
        return -1;
    }

    // load and compile fragment shader
    std::string fragShaderSrc = loadShaderFromFile(FRAGMENT_SHADER_FILENAME);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    p = fragShaderSrc.c_str();
    glShaderSource(fragShader, 1, &p, nullptr);
    glCompileShader(fragShader);

    success = GL_FALSE;
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        GLint len;
        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &len);
        std::string logInfo(len - 1, 0); // as null terminator is contained in the length
        glGetShaderInfoLog(fragShader, len, nullptr, &logInfo[0]);
        std::cout << "compile info for fragment shader : " << std::endl
        << logInfo << std::endl;
        return -1;
    }



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