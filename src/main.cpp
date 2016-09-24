

int hello_world();
int hello_triangle();
int hello_triangle_with_element_buffer();

#define TEST hello_triangle_with_element_buffer

int main(void)
{
    return TEST();
}