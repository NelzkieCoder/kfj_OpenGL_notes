

int hello_world();
int hello_triangle();
int hello_triangle_with_element_buffer();
int hello_two_triangles();
int hello_two_triangles_2();

#define TEST hello_two_triangles_2

int main(void)
{
    return TEST();
}