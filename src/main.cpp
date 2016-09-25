

int hello_world();
int hello_triangle();
int hello_triangle_with_element_buffer();
int hello_two_triangles();
int hello_two_triangles_2();
int hello_two_triangles_2_with_different_color();
int hello_circle();

#define TEST hello_circle

int main(void)
{
    return TEST();
}