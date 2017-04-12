#include <string>
#include "common.hpp"
#include "shader.hpp"

//! Specify a horizontal offset via a uniform and move the triangle to
//! the right side of the screen in the vertex shader using this offset value
//! Solution code: https://learnopengl.com/code_viewer.php?code=getting-started/shaders-exercise2
//!
//! @sa ex01_01_hello_triangle,ex02_hello_triangle,ex03_hello_triangle
//! @image html pic/exercises/hello-shader-ex02.png "Output"
int ex02_hello_shaders()
{
  std::string vertex_source =
  "#version 330 core" "\n"
  "layout (location = 0) in vec2 pos;"  "\n"
  "layout (location = 1) in vec3 in_color;"  "\n"
  "uniform vec2 offset;" "\n" // !!! use uniform !!!
  "out vec4 color;" "\n"
  "void main()" "\n"
  "{" "\n"
  "   gl_Position = vec4(pos+offset, 0.0, 1.0);" "\n" // plus offset
  "   color = vec4(in_color, 1.0f);" "\n"
  "}"
  ;

  std::string fragment_source =
  "#version 330 core"  "\n"
  "in vec4 color;"
  "out vec4 c;"  "\n"
  "void main()"   "\n"
  "{"   "\n"
  "   c = color;"  "\n"
  "}"
  ;

  GLFWwindow *window;
  create_context(&window, 500, 500);

  Shader shader;
  shader.setVertexShaderSource(vertex_source);
  shader.setFragmentShaderSource(fragment_source);
  shader.linkProgram();

  GLfloat vertices[] = {
          // first triangle
          -0.5f, 0.0f, // 0, left vertex
          0.5f, 0.0f,  // 1, right vertex
          0.0f, 0.5f,   // 2, top vertex
          1, 0, 0, // red, color of the left vertex
          0, 1, 0, // green, color of the right vertex
          0, 0, 1, // blue, color of the top vertex
  };

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER ,vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(
          0, // index, which attribute
          2, // number of component per vertex attribute
          GL_FLOAT, // data type of each component
          GL_FALSE, // need to be normalized ?
          0,  // stride, 0 -> compact
          nullptr);   // offset
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(
          1, // index, which attribute
          3, // number of component per vertex attribute
          GL_FLOAT, // data type of each component
          GL_FALSE, // need to be normalized ?
          0,  // stride, 0 -> compact
          (const void*)(6*sizeof(GLfloat)));   // offset
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);   // reset
  glBindVertexArray(0);

  // commet it out to fill the triangle
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  shader.useProgram();
  GLint offset_location = glGetUniformLocation(shader.getProgram(), "offset");
  glUniform2f(offset_location, 0.4, 0.4); // offset (0.4, 0.4)

  while(!glfwWindowShouldClose(window))
  {
      glfwPollEvents();

      // clear the color buffer, RGBA
      glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // draw the triangle
      glBindVertexArray(vao);
      glDrawArrays(
              GL_TRIANGLES, // primitives
              0, // starting index
              3 // number of indices
      );
      glBindVertexArray(0); // reset;

      glfwSwapBuffers(window);
  }

  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);

  glfwTerminate();

  return 0;
}
