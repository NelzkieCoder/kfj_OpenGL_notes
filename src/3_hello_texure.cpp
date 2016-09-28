//
// Created by fangjun on 28/09/16.
//

// use of texture

/*
 *
 * For the explanation to the code, refer to http://learnopengl.com/#!Getting-started/Textures
 * Refer to http://learnopengl.com/code_viewer.php?code=getting-started/textures_combined for the original source code
 *
 */



#include <iostream>

// https://github.com/smibarber/libSOIL
#include "SOIL.h"

// texture image 1
const static std::string kImg1 = "pic/wall.jpg";



int hello_texture()
{
    // Load image
    int width, height;
    unsigned char* image1 = SOIL_load_image(kImg1.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    std::cout << "(" << width << ", " << height << ")" << std::endl;

    return 0;
}
