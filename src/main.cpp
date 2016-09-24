

int hello_world();
int hello_triangle();

#define TEST hello_triangle

int main(void)
{
    return TEST();
}