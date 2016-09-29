//
// Created by fangjun on 29/09/16.
//


#include <glm/glm.hpp>
#include <iostream>

int test_glm()
{

    // [0;0]
    glm::vec2 v1;

    // [1; 1]
    glm::vec2 v2(1.0f);

    // [1; 2]
    glm::vec2 v3(1.0f, 2.0f);

    // [1;1;1]
    glm::vec3 v4(1.0f);

    // [1; 2; 3]
    glm::vec3 v5(1.0f, 2.0f, 3.0f);

    // [0; 0; 0]
    glm::vec3 v6;

    // [1; 1; 5]
    glm::vec3 v(v2, 5);

    // identity matrix
    glm::mat4 m2;

    // identity matrix too
    glm::mat4 m3 = glm::mat4(1.0f);

    // last column, column major!
    m3[3] = glm::vec4(1.0f, 2.0f, 3.0f, 1.0f);

    glm::vec4 v7(1.0f, 1.0f, 1.0f, 1.0f);

    // [2, 3, 4, 1]
    glm::vec4 m = m3 * v7;

    for(int r = 0; r < 4; ++r) {
        //for (int c = 0; c < 4; ++c)
            //std::cout << m[c][r] << ",";
        std::cout << m[r] << "," << std::endl;
    }

    return 0;
}

