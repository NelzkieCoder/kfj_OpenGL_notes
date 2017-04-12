//
// Created by fangjun on 29/09/16.
//



#include <glm/glm.hpp>  // /usr/local/include/glm/glm.hpp
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <sstream>

//! Usage of GLM
//!
//! The header file is in `/usr/local/include/glm/glm.hpp`
//! or it can be found in `/usr/local/Cellar/glm/0.9.7.4/include`
//! after using `brew install glm` on Mac OS X.
//!
//! <h3>References</h3>
//! - Manual: http://glm.g-truc.net/0.9.5/glm-0.9.5.pdf
int test_glm()
{
    std::stringstream ss;
    // [0;0]
    glm::vec2 v1;
    ss << "v1: (" << v1.x << ", " << v1.y << ")" << std::endl;

    // [1; 1]
    glm::vec2 v2(1.0f);
    ss << "v2: (" << v2.x << ", " << v2.y << ")" << std::endl;

    // [1; 2]
    glm::vec2 v3(1.0f, 2.0f);
    ss << "v3: (" << v3.x << ", " << v3.y << ")" << std::endl;

    // [1;1;1]
    glm::vec3 v4(1.0f);

    // [1; 2; 3]
    glm::vec3 v5(1.0f, 2.0f, 3.0f);

    // [0; 0; 0]
    glm::vec3 v6;

    // glm::vec3 v77(1.0f, 2.0f);  // compilation error !

    // [1; 1; 5]
    glm::vec3 v(v2, 5);

    // 4-by-4, identity matrix
    glm::mat4 m2;

    // identity matrix too
    glm::mat4 m3 = glm::mat4(1.0f);

    // last column, column major!
    // translation matrix
    m3[3] = glm::vec4(1.0f, 2.0f, 3.0f, 1.0f);

    glm::vec4 v7(1.0f, 1.0f, 1.0f, 1.0f);

    // [2, 3, 4, 1]
    glm::vec4 m = m3 * v7;

    // counterclockwise 30 degrees. Note that it is in radian by default!
    // Use glm::radians to convert degree to radian.
    /*
      sqrt(3)/2  -0.5        0  0
      0.5        sqrt(3)/2   0  0
      0           0          1  0
      0           0          0  1
    */
    glm::mat4 rotation_z_30;
    rotation_z_30 = glm::rotate(rotation_z_30, glm::radians(30.0f), glm::vec3(0,0,1));

    /*
      1 0 0 1
      0 1 0 2
      0 0 1 3
      0 0 0 1
    */
    glm::mat4 translate_mat;
    translate_mat = glm::translate(translate_mat, glm::vec3(1,2,3));

    /*
      1 0 0 0
      0 2 0 0
      0 0 3 0
      0 0 0 1
    */
    glm::mat4 scale_mat;
    scale_mat = glm::scale(scale_mat, glm::vec3(1,2,3));

    //std::cout << ss.str() << std::endl;

    for(int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c)
            std::cout << rotation_z_30[c][r] << ","; // note that m[0] means column 0, not row 0!
        std::cout << std::endl;
        //std::cout << m2[r] << "," << std::endl;
    }

    return 0;
}
