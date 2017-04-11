#include <string>
#include "common.hpp"
#include "shader.hpp"

//! Try to draw 2 triangles next to each other using
//! `glDrawElements` by adding more vertices to your data.
//! It uses `glDrawElements`.
//! Solution code: https://learnopengl.com/code_viewer.php?code=getting-started/hello-triangle-exercise1
//! @sa ex01_hello_triangle,ex02_hello_triangle,ex03_hello_triangle
//! @image html pic/exercises/hello-triangle-ex01-01.png "Output"
int ex01_01_hello_triangle()
{
  std::string vertex_source =
  "#version 330 core" "\n"
  "layout (location = 0) in vec2 pos;"  "\n"
  "void main()" "\n"
  "{" "\n"
  "gl_Position = vec4(pos, 0.0, 1.0);" "\n"
  "}"
  ;

  std::string fragment_source =
  "#version 330 core"  "\n"
  "out vec4 color;"  "\n"
  "void main()"   "\n"
  "{"   "\n"
  "color = vec4(0.0f, 1.0f, 0.0f, 1.0f);"  "\n"
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
          -0.1f, 0.0f,  // 1, right vertex
          -0.1f, 0.5f,   // 2, top vertex
          // second triangle
          0.5f, 0.0f, // 0, right vertex
          0.1f, 0.0f, // 1, left vertex
          0.1f, 0.5f, // 2, top vertex
  };

  GLuint indices[] = {
          0,1,2,  // first triangle
          3,4,5,  // second triangle
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
          0,  // stride, 0 -> compact, OpenGL will compute it. non-zero --> number of bytes between two consecutive vertices
          nullptr);   // offset

  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);   // reset
  glBindVertexArray(0);

  // commet it out to fill the triangle
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  shader.useProgram();
  while(!glfwWindowShouldClose(window))
  {
      glfwPollEvents();

      // clear the color buffer, RGBA
      glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // draw the triangle
      glBindVertexArray(vao);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
      glBindVertexArray(0); // reset;

      glfwSwapBuffers(window);
  }

  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);

  glfwTerminate();

  return 0;
}
