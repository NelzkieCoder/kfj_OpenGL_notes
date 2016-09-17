cmake_minimum_required(VERSION 3.5)
project(kfj_OpenGL_notes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

IF (APPLE)
    include_directories (/System/Library/Frameworks)
    find_library (GLUT_LIBRARY GLUT)
    find_library (OpenGL_LIBRARY OpenGL)
    mark_as_advanced (GLUT_LIBRARY
            OpenGL_LIBRARY)
    set (EXTRA_LIBS ${GLUT_LIBRARY} ${OpenGL_LIBRARY})
ENDIF (APPLE)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

set(SOURCE_FILES src/main.cpp)
add_executable(kfj_OpenGL_notes ${SOURCE_FILES})


target_link_libraries(kfj_OpenGL_notes ${EXTRA_LIBS})