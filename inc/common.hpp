// Note: include GLEW before GLFW !!!
// #define GLEW_STATIC  // to link statically

// GLEW
// #define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

//! Create an OpenGL context
//!
//! @param window [out] Pointer to the created window.
//! @param width  [in]  Window width
//! @param height [in]  Window height
//! @return -1 on error, 0 on success
int create_context(GLFWwindow **window, GLint width = 800, GLint height = 600);

//! keyboard callback function.
//!
//! Press Esc to close a window.
//!
//! @param window   [in] The window in which the key is pressed/released
//! @param key      [in] The key that has been pressed/released
//! @param scancode [in]
//! @param action   [in] GLFW_RELEASE for key released; GLFW_PRESS for key pressed
//! @param mode     [in]
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

//! Read a text file and save the content in a std::string
//! @param filename [in] Path to the file to be read.
//! @return The content of the file.
std::string load_shader_from_file(const std::string& filename);

//! Path to the shader files.
const static std::string g_shader_path = "/Users/fangjun/Documents/bitbucket/kfj_OpenGL_notes";

//! Path to the images
const static std::string g_pic_path = "/Users/fangjun/Documents/bitbucket/kfj_OpenGL_notes";
