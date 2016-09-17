cmake_minimum_required(VERSION 3.5)
project(kfj_OpenGL_notes)

# /System/Library/Frameworks/OpenGL.framework
# set(CMAKE_PREFIX_PATH /usr/local/Cellar/glfw3/3.2.1)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# /usr/local/Cellar/glfw3/3.2.1/lib/libglfw3.dylib
# brew update
# brew tap homebrew/versions
# brew install glfw3

link_directories(/usr/local/Cellar/glfw3/3.2.1/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lglfw3  -framework OpenGL")


include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

set(SOURCE_FILES src/main.cpp)
add_executable(kfj_OpenGL_notes ${SOURCE_FILES})
