cmake_minimum_required(VERSION 3.5)
project(kfj_OpenGL_notes)

# /System/Library/Frameworks/OpenGL.framework
# set(CMAKE_PREFIX_PATH /usr/local/Cellar/glfw3/3.2.1)

# set(CMAKE_PREFIX_PATH /usr/local/Cellar/glew)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

if (true)
  # refer to Useful GCC flags for C, http://stackoverflow.com/questions/3375697/useful-gcc-flags-for-c
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wunreachable-code")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-align -Wstrict-prototypes -Wstrict-prototypes")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-overflow=5 -Wwrite-strings -Waggregate-return")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual -Wswitch-default -Wswitch-enum -Wconversion")
endif()

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

#============================================================================
# libSOIL, The Simple OpenGL Image Library for Mac OS X
#----------------------------------------------------------------------------
# source code is at https://github.com/smibarber/libSOIL
# the compile library is saved in the lib/ directory
# its header file is in in/ directory
# set DYLD_LIBRARY_PATH when running the program, because it is dynamic linked!


set(myLib  "-lSOIL -lglfw3 -lGLEW -framework OpenGL")

set(CMAKE_CXX_LINK_FLAGS  "${CMAKE_CXX_LINK_FLAGS} ${myLib}")

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
        /usr/local/Cellar/glm/0.9.7.4/include   # for GLM, brew install glm
)

set(SOURCE_FILES
        src/main.cpp
        src/util.cpp
        src/common.cpp
        src/shader.cpp
        src/printsysteminfo.cpp
        )

set(SOURCE_FILES
    ${SOURCE_FILES}
    src/1_hello_world.cpp
    src/2_hello_triangle.cpp
    src/2_hello_triangle_with_element_buffer.cpp
    src/2_hello_two_triangles.cpp
    src/2_hello_two_triangles_2.cpp
    src/2_hello_two_triangles_2_with_different_color.cpp
    src/2_hello_circle.cpp
    src/3_hello_triangle_uniform.cpp
    src/3_hello_triangle_color.cpp
    src/4_hello_texture.cpp
    src/5_test_GLM.cpp
    )

set(SOURCE_FILES
    ${SOURCE_FILES}
    src/exercises/hello-triangle-ex01.cpp
    src/exercises/hello-triangle-ex01-01.cpp
    src/exercises/hello-triangle-ex02.cpp
    src/exercises/hello-triangle-ex03.cpp
)
add_executable(kfj_OpenGL_notes ${SOURCE_FILES})


#target_link_libraries(kfj_OpenGL_notes ${CMAKE_SOURCE_DIR}/lib/libSOIL.a)
