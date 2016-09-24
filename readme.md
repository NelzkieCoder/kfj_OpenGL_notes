# Introduction
 This repsoitory contains my notes while learning computer graphics.

 The IDE used is [CLion][1]. Its configuration file on Mac OS x is `~/Library/Preferences/CLion2016.1`.


# TODO
 - ~~[Draw a triangle][19]~~ -> [2_hello_triangle.cpp][21]
   - Use element buffer
   - draw two triangles
   - draw a circle



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
