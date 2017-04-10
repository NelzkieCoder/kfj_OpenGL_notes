
# Pass data from the .cpp code to the vertex shader
In general there are two methods for passing data from
the .cpp code to the vertex shader.

# Method 1
The example of `Hello Triangle` at <https://learnopengl.com/#!Getting-started/Hello-Triangle>
shows one example.

Inside the vertex shader:
```.cpp
layout (location = 0) in vec3 p;
layout (location = 1) in vec3 our_color;
```

Inside the .cpp code
```.cpp
glEnableVertexAttribArray(0);
glVertexAttribPointer(0,....);

glEnableVertexAttribArray(1);
glVertexAttribPointer(1,....);
```

That is, we specify the location explicitly inside the vertex shader.

# Method 2
The example of `Drawing polygons` at <https://open.gl/drawing> shows an
another example.

Inside the vertex shader:
```.cpp
in vec2 position;
```

Inside the .cpp code:

```.cpp
glLinkProgram(shaderProgram);
// after linking...
GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
glEnableVertexAttribArray(posAttrib);
glVertexAttribPointer(posAttrib,...);
```
That is, we need to know the variable name in the vertex shader instead of
its location. The linked program object handles its location.

# Pass data from the vertex shader to the fragment shader
