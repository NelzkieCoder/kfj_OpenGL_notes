//! @mainpage OpenGL notes
//!
//!  This repository contains my notes while learning OpenGL.
//!
//!  To run doxygen from the commandline:
//!  @code
//!  doxygen Doxyfile_kfj
//!  @endcode
//!
//!  <h3>Examples</h3>
//!  - @ref print_system_info, print system information, such as vendor, OpenGL version, etc.
//!  - @ref hello_world, display a window
//!  - @ref hello_triangle, draw a triangle
//!  - @ref hello_triangle_with_element_buffer, draw two triangles
//!  - @ref hello_circle, draw a circle
//!  - @ref hello_two_triangles_2_with_different_color, draw two triangles with different colors
//!  - @ref hello_texture, use of texutre
//!
//!  <h3>Exercises</h3>
//!  - @ref ex01_hello_shaders
//!  - @ref ex01_01_hello_triangle
//!  - @ref ex01_hello_triangle
//!  - @ref ex02_hello_triangle
//!  - @ref ex03_hello_triangle
//!  - @ref ex01_hello_shaders
//!
//!  <h3>References</h3>
//!   -# [Tips for writing doxygen documentation](https://www.rosettacommons.org/manuals/rosetta3.2_user_guide/doxygen_tips.html)


//! @defgroup group_basics Basics




int hello_world();  // 0
int hello_triangle(); // 1
int hello_triangle_with_element_buffer(); // 2
int hello_circle();  // 3
int hello_two_triangles_2_with_different_color(); // 4
int hello_two_triangles();
int hello_two_triangles_2();


int hello_triangle_uniform();
int hello_triangle_color();
int hello_texture();
int test_glm();

int print_system_info();

//===============
// Exercises
//---------------
int ex01_hello_triangle();
int ex01_01_hello_triangle();
int ex02_hello_triangle();
int ex03_hello_triangle();
int ex01_hello_shaders();
int ex02_hello_shaders();
int texture_exercise();

int ex01_glm();

#define TEST ex01_glm

int main(void)
{
    return TEST();
}
