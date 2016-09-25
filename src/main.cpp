

int hello_world();
int hello_triangle();
int hello_triangle_with_element_buffer();
int hello_two_triangles();

#define TEST hello_two_triangles

int main(void)
{
    return TEST();
}