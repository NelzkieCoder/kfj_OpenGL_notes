
// /usr/local/include/glm/glm.hpp
#include <glm/glm.hpp>  // mat4, vec4, etc.
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp> // value_ptr

#include "common.hpp"
#include "shader.hpp"

//! rotate counterclockwise, degrees
static float angles = 30;

//! Press the arrow key "upward" and "downward" to rotate the line!
static void my_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // close the window when Esc is pressed
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, GL_TRUE);
    } else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
      angles += 10.0f;
    } else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
      angles -= 10.0f;
    }
}

//! Rotate a line by specified degrees, counterclockwise
//! Press the arrow key "upward" or "downward" to rotate.
//! @image html pic/exercises/glm_ex01.png "Output"
int ex01_glm()
{
  std::string vertex_source1 =
  "#version 330 core" "\n"
  "layout (location = 0) in vec2 pos;"  "\n"
  "uniform mat4 m;"
  "void main()" "\n"
  "{" "\n"
  "   gl_Position = m*vec4(pos, 0.0, 1.0);" "\n"  // transform the vertices
  "}"
  ;

  std::string vertex_source2 =
  "#version 330 core" "\n"
  "layout (location = 0) in vec2 pos;"  "\n"
  "void main()" "\n"
  "{" "\n"
  "   gl_Position = vec4(pos, 0.0, 1.0);" "\n"  // without transformations
  "}"
  ;

  std::string fragment_source =
  "#version 330 core"  "\n"
  "out vec4 color;"  "\n"
  "void main()"   "\n"
  "{"   "\n"
  "   color = vec4(1, 0, 0, 1);"  "\n"
  "}"
  ;

  std::string fragment_source2 =
  "#version 330 core"  "\n"
  "out vec4 color;"  "\n"
  "void main()"   "\n"
  "{"   "\n"
  "   color = vec4(0, 1, 0, 1);"  "\n"
  "}"
  ;

  GLFWwindow *window;
  create_context(&window);
  glfwSetKeyCallback(window, my_key_callback);

  Shader shader1;
  shader1.setVertexShaderSource(vertex_source1);
  shader1.setFragmentShaderSource(fragment_source);
  shader1.linkProgram();

  Shader shader2;
  shader2.setVertexShaderSource(vertex_source2);
  shader2.setFragmentShaderSource(fragment_source2);
  shader2.linkProgram();

  GLfloat vertices[] = {
    0, 0,   // first point
    0.5, 0, // second point
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
          0,  // stride
          nullptr);   // offset

  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);   // reset
  glBindVertexArray(0);

  glm::mat4 rotation_mat;
  glm::mat4 identity_mat;

  GLint transformLoc = glGetUniformLocation(shader1.getProgram(), "m");

  while(!glfwWindowShouldClose(window))
  {
      glfwPollEvents();

      // clear the color buffer, RGBA
      glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      shader1.useProgram();
      rotation_mat = glm::rotate(identity_mat, glm::radians(angles), glm::vec3(0,0,1));
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(rotation_mat));

      // draw the triangle
      glBindVertexArray(vao);
      glDrawArrays(GL_LINES, 0, 2);

      shader2.useProgram();
      glDrawArrays(GL_LINES, 0, 2);

      glBindVertexArray(0); // reset;

      glfwSwapBuffers(window);
  }

  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);

  glfwTerminate();

  return 0;
}
