#include <string>
#include "common.hpp"
#include "shader.hpp"

//! Create two shader programs where the second program uses a
//! different fragment shader that outputs the color yellow;
//! draw both triangles again where one outputs the color yellow.
//! Solution code: https://learnopengl.com/code_viewer.php?code=getting-started/hello-triangle-exercise3
//! @sa ex01_hello_triangle,ex02_hello_triangle,ex01_01_hello_triangle
//! @image html pic/exercises/hello-triangle-ex03.png "Output"
int ex03_hello_triangle()
{
  std::string vertex_source =
  "#version 330 core" "\n"
  "layout (location = 0) in vec2 pos;"  "\n"
  "void main()" "\n"
  "{" "\n"
  "gl_Position = vec4(pos, 0.0, 1.0);" "\n"
  "}"
  ;

  // red
  std::string fragment_source =
  "#version 330 core"  "\n"
  "out vec4 color;"  "\n"
  "void main()"   "\n"
  "{"   "\n"
  "color = vec4(1.0f, 0.0f, 0.0f, 1.0f);"  "\n"
  "}"
  ;

  // yellow
  std::string fragment_source2 =
  "#version 330 core"  "\n"
  "out vec4 color;"  "\n"
  "void main()"   "\n"
  "{"   "\n"
  "color = vec4(1.0f, 1.0f, 0.0f, 1.0f);"  "\n"
  "}"
  ;

  GLFWwindow *window;
  create_context(&window, 500, 500);

  Shader shader;
  shader.setVertexShaderSource(vertex_source);
  shader.setFragmentShaderSource(fragment_source);
  shader.linkProgram();

  Shader shader2;
  shader2.setVertexShaderSource(vertex_source);
  shader2.setFragmentShaderSource(fragment_source2);
  shader2.linkProgram();

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

  glBindBuffer(GL_ARRAY_BUFFER, 0);   // reset
  glBindVertexArray(0);

  // commet it out to fill the triangle
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while(!glfwWindowShouldClose(window))
  {
      glfwPollEvents();

      // clear the color buffer, RGBA
      glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      shader.useProgram();
      // draw the triangle
      glBindVertexArray(vao);
      glDrawArrays(
              GL_TRIANGLES, // primitives
              0, // starting index
              3 // number of indices
      );

      shader2.useProgram();
      glDrawArrays(
              GL_TRIANGLES, // primitives
              3, // starting index
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
