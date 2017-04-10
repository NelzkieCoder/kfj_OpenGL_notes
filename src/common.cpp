/**
 @file common.cpp
 Common code for configuring the context.
*/

#include "common.hpp"

int create_context(GLFWwindow **window, GLint width, GLint height)
{
  glfwInit();

  // refer to http://www.glfw.org/docs/latest/window.html#window_hints
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  *window = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);
  if (*window == nullptr)
  {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
  }
  glfwMakeContextCurrent(*window);

  // Set the required callback functions
  glfwSetKeyCallback(*window, key_callback);

  // initialize GLEW

  // true -> to use modern techniques
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
  {
      std::cout << "Failed to initialize GLEW" << std::endl;
      return -1;
  }

  // set viewport
  int w, h;
  glfwGetFramebufferSize(*window, &w, &h);

  // map normalized device coordinates
  // [-1, 1] --> [0, 800]
  //             [0, 600]
  glViewport(0, 0, w, h);
  return 0;
}
