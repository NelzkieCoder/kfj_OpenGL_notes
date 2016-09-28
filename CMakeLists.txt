cmake_minimum_required(VERSION 3.5)
project(kfj_OpenGL_notes)

# /System/Library/Frameworks/OpenGL.framework
# set(CMAKE_PREFIX_PATH /usr/local/Cellar/glfw3/3.2.1)

# set(CMAKE_PREFIX_PATH /usr/local/Cellar/glew)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# /usr/local/Cellar/glfw3/3.2.1/lib/libglfw3.dylib
# brew update
# brew tap homebrew/versions
# brew install glfw3

# /usr/local/Cellar/glew/1.13.0/lib/libGLEW.dylib
# /usr/local/Cellar/glew/1.13.0/lib/libGLEW.a
# /usr/local/Cellar/glew/1.13.0/lib/libGLEWmx.dylib
# /usr/local/Cellar/glew/1.13.0/lib/libGLEWmx.a

# brew install glew

link_directories(
        /usr/local/Cellar/glfw3/3.2.1/lib
        /usr/local/Cellar/glew/1.13.0/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

# libSOIL.dylib  -> https://github.com/smibarber/libSOIL
# set DYLD_LIBRARY_PATH when run the program, because it is dynamic linked!
set(myLib  "-lSOIL -lglfw3 -lGLEW -framework OpenGL")

set(CMAKE_CXX_LINK_FLAGS  "${CMAKE_CXX_LINK_FLAGS} ${myLib}")


include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

set(SOURCE_FILES
        src/main.cpp
        src/util.cpp
        src/1_hello_world.cpp
        src/2_hello_triangle.cpp
        src/2_hello_triangle_with_element_buffer.cpp
        src/2_hello_two_triangles.cpp
        src/2_hello_two_triangles_2.cpp
        src/2_hello_two_triangles_2_with_different_color.cpp
        src/2_hello_circle.cpp
        src/3_hello_triangle_uniform.cpp
        src/3_hello_triangle_color.cpp
        src/util.cpp
        src/Shader.cpp src/3_hello_texure.cpp)
add_executable(kfj_OpenGL_notes ${SOURCE_FILES})


#target_link_libraries(kfj_OpenGL_notes ${CMAKE_SOURCE_DIR}/lib/libSOIL.a)