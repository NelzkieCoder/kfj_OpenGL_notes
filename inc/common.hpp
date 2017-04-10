// Note: include GLEW before GLFW !!!
// #define GLEW_STATIC  // to link statically

// GLEW
// #define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <iostream>

//! Create an OpenGL context
//! @param window [out] Pointer to the created window.
//! @return -1 on error, 0 on success
int create_context(GLFWwindow **window);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
