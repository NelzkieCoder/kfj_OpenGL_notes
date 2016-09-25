

int hello_world();
int hello_triangle();
int hello_triangle_with_element_buffer();
int hello_two_triangles();
int hello_two_triangles_2();
int hello_two_triangles_2_with_different_color();
int hello_circle();
int hello_triangle_uniform();

#define TEST hello_triangle_uniform

int main(void)
{
    return TEST();
}