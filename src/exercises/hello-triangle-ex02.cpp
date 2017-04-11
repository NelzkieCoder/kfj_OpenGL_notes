#include <string>
#include "common.hpp"
#include "shader.hpp"

//! Now create the same 2 triangles using two different VAOs and VBOs for their data
//! Solution code: https://learnopengl.com/code_viewer.php?code=getting-started/hello-triangle-exercise2
//! @sa ex01_hello_triangle, ex01_01_hello_triangle,ex03_hello_triangle
//! @image html pic/exercises/hello-triangle-ex02.png "Output"
int ex02_hello_triangle()
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
  "color = vec4(0.0f, 1.0f, 1.0f, 1.0f);"  "\n"
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
          -0.1f, -0.5f,   // 2, top vertex
          // second triangle
          0.5f, 0.0f, // 0, right vertex
          0.1f, 0.0f, // 1, left vertex
          0.1f, 0.6f, // 2, top vertex
  };

  GLuint indices[] = {
          0,1,2,  // first triangle
          0,1,2,  // second triangle, as we use the same array to save the vertices
  };

  GLuint vao[2];
  glGenVertexArrays(2, vao);
  glBindVertexArray(vao[0]);

  GLuint vbo[2];
  glGenBuffers(2, vbo);
  glBindBuffer(GL_ARRAY_BUFFER ,vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*6, vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
          0, // index, which attribute
          2, // number of component per vertex attribute
          GL_FLOAT, // data type of each component
          GL_FALSE, // need to be normalized ?
          0,  // stride, 0 -> compact
          nullptr);   // offset

  GLuint ebo[2];
  glGenBuffers(2, ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0])*3, indices, GL_STATIC_DRAW);

  glBindVertexArray(vao[1]);
  glBindBuffer(GL_ARRAY_BUFFER ,vbo[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*6, vertices+6, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
          0, // index, which attribute
          2, // number of component per vertex attribute
          GL_FLOAT, // data type of each component
          GL_FALSE, // need to be normalized ?
          0,  // stride, 0 -> compact
          nullptr);   // offset
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0])*3, indices+3, GL_STATIC_DRAW);


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
      glBindVertexArray(vao[0]);
      glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

      // draw the triangle
      glBindVertexArray(vao[1]);
      glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

      glBindVertexArray(0); // reset;

      glfwSwapBuffers(window);
  }

  glDeleteBuffers(2, ebo);
  glDeleteBuffers(2, vbo);
  glDeleteVertexArrays(2, vao);

  glfwTerminate();

  return 0;
}
