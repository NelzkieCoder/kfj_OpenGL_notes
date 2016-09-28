# Introduction
 This repsoitory contains my notes while learning computer graphics.

 The IDE used is [CLion][1]. Its configuration file on Mac OS x is `~/Library/Preferences/CLion2016.1`.


# TODO
 - ~~[Draw a triangle][19]~~ -> [2_hello_triangle.cpp][21], [2_hello_triangle_with_element_buffer.cpp][25]
   - ~~Use element buffer~~ -> [2_hello_triangle_with_element_buffer.cpp][22]
   - ~~draw two triangles~~ -> [2_hello_two_triangles.cpp][26], [2_hello_two_triangles_2.cpp][27], [2_hello_two_triangles_2_with_different_color.cpp][28]
   - ~~draw a circle~~ -> [2_hello_circle.cpp][24]
 - ~~[Shaders][29]~~
    - [3_hello_triangle_color.cpp][34]
    - [3_hello_triangle_uniform.cpp][35]
 - [Textures][30]
    - [4_hello_texture.cpp][39]
 - [Transformations][31]
 - [Coordinate Systems][32]
 - [Camera][33]



## API manual
 - [OpenGL 4.5 Reference Pages][6]
 - [OpenGL Registry][8], information for various versions of OpenGL.

## GLSL
 - [OpenGL Shading Language][20], Wikipedia

## Tutorials
 - [OpenGL tutorials][2], `http://www.opengl-tutorial.org`
 - [OpenGL dev - Modern OpenGL tutorial][3], `http://ogldev.atspace.co.uk`
 - [**Learn OpenGL**][4], `http://learnopengl.com` and its [Chinese translation][9]
    - The tutorials in this site use OpenCL 3.3. OpenGL core profile is supported since OpenGL 3.2.
    - A good starting point for learning OpenGL is version 3.3. Versions greater than 3.3 just add
    some new features.
    - Only latest graphics card drivers support the latest OpenGL !
    - OpenGL libraries are written in **C** language!
 - [OpenGL Programming Book][5], `https://en.wikibooks.org/wiki/OpenGL_Programming`
 - [Learn OpenGL ES][7]
 - [**Anton's OpenGL 4 Tutorials**][23]
 - [open.gl][36], `https://open.gl`, which is written by [**Alexander Overvoorde**][37]
    - He also writes excellent [Vulkan Tutorial][38]


## Tools
 - [**GLFW**][10], [source code][14] on GitHub
 - [SDL][11], Simple DirectMedia Layer
 - [SFML][12], Simple and Fast Multimedia Library
 - [Allegro][13], a game programming library
 - [GLEW][15], The OpenGL Extension Wrangler Library
    - install: `brew install glew`
    - location: `/usr/local/Cellar/glew/1.13.0`
 - [GLM][16], OpenGL Mathematics
 - [Vulkan (API)][17]
 - [Metal for Developers][18], by Apple

## Install GLFW on Mac OS x
 - install brew , then add path `/usr/local/bin/brew`

```
brew update
brew tap homebrew/versions
brew install glfw3
# or install version 2
# /usr/local/Cellar/glfw2/2.7.9
brew install glfw2

# or static build
# /usr/local/Cellar/glfw3/3.2.1
brew install --static glfw3

brew install --static glew
```

 - lib: `/usr/local/lib`, `/usr/local/Cellar/glfw3/3.2.1/lib`
 - header: `/usr/local/include`, `/usr/local/Cellar/glfw3/3.2.1/include`
 - link: `-framework OpenGl -lglfw3`


# SOIL library
 - go to `https://github.com/smibarber/libSOIL` and download `.zip` file
 - unzip
 - go to directory `libSOIL-master`
 - `make`
 - copy `libSOIL-master/libSOIL.dylib`
 - `export DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}:/Users/fangjun/Documents/bitbucket/kfj_OpenGL_notes/lib`




[39]: https://github.com/csukuangfj/kfj_OpenGL_notes/blob/master/src/4_hello_texture.cpp
[38]: https://vulkan-tutorial.com
[37]: https://while.io
[36]: https://open.gl
[35]: https://github.com/csukuangfj/kfj_OpenGL_notes/blob/master/src/3_hello_triangle_uniform.cpp
[34]: https://github.com/csukuangfj/kfj_OpenGL_notes/blob/master/src/3_hello_triangle_color.cpp
[33]: http://learnopengl.com/#!Getting-started/Camera
[32]: http://learnopengl.com/#!Getting-started/Coordinate-Systems
[31]: http://learnopengl.com/#!Getting-started/Transformations
[30]: http://learnopengl.com/#!Getting-started/Textures
[29]: http://learnopengl.com/#!Getting-started/Shaders
[28]: https://github.com/csukuangfj/kfj_OpenGL_notes/blob/master/src/2_hello_two_triangles_2_with_different_color.cpp
[27]: https://github.com/csukuangfj/kfj_OpenGL_notes/blob/master/src/2_hello_two_triangles_2.cpp
[26]: https://github.com/csukuangfj/kfj_OpenGL_notes/blob/master/src/2_hello_two_triangles.cpp
[25]: https://github.com/csukuangfj/kfj_OpenGL_notes/blob/master/src/2_hello_triangle_with_element_buffer.cpp
[24]: https://github.com/csukuangfj/kfj_OpenGL_notes/blob/master/src/2_hello_circle.cpp
[23]: http://antongerdelan.net/opengl/index.html
[22]: https://github.com/csukuangfj/kfj_OpenGL_notes/blob/master/src/2_hello_triangle_with_element_buffer.cpp
[21]: https://github.com/csukuangfj/kfj_OpenGL_notes/blob/master/src/2_hello_triangle.cpp
[20]: https://en.wikipedia.org/wiki/OpenGL_Shading_Language
[19]: http://learnopengl.com/#!Getting-started/Hello-Triangle
[18]: https://developer.apple.com/metal/
[17]: https://en.wikipedia.org/wiki/Vulkan_(API)
[16]: https://github.com/g-truc/glm
[15]: http://glew.sourceforge.net
[14]: https://github.com/glfw/glfw
[13]: http://liballeg.org/index.html
[12]: http://www.sfml-dev.org
[11]: http://www.libsdl.org/index.php
[10]: http://www.glfw.org
[9]: https://learnopengl-cn.github.io
[8]: https://www.opengl.org/registry/
[7]: http://www.learnopengles.com
[6]: https://www.opengl.org/sdk/docs/man/
[5]: https://en.wikibooks.org/wiki/OpenGL_Programming
[4]: http://learnopengl.com
[3]: http://ogldev.atspace.co.uk
[2]: http://www.opengl-tutorial.org
[1]: https://www.jetbrains.com/clion/
