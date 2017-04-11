
# Output of a vertex shader
 - `gl_Position`: this is a predefined variable, it stores the normalized coordinate
of each  vertex. We do not need to delcare it, instead we use it directly! For example,
```.cpp
gl_Position = vec4(1.0, 0.0, 0.0, 1.0);
```
Note that it is of type `vec4`.
 - Other variables, for example,
```.cpp
out vec4 color;
```
The output variable is declared with `out`. The name of the variable is **arbitrary**!
In order to access the output of the vertex shader from the fragment shader, it should
use the same name in the fragment shader. For the example above, the fragment code
should use the following code:
```.cpp
in vec4 color;
```

# Input of a vertex shader
Note that the name of the input variable can be arbitrary!
 - Style 1
```.cpp
layout (location = 0) in vec3 p;
```
That is, it specifies the location of the variable. So it can use
`glVertexAttribPointer` to pass data to it from the .cpp code.

 - Style 2
```.cpp
in vec3 p
```
It does not sepecify the location. In order to initialize this variable,
the .cpp code should use:
```.cpp
GLint posAttrib = glGetAttribLocation(shaderProgram, "p");
glVertexAttribPointer(posAttrib,...);
```


# Pass data from the .cpp code to the vertex shader
In general there are three methods for passing data from
the .cpp code to the vertex shader.

## Method 1
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

## Method 2
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

## Method 3
Use uniform.

Inside the vertex shader code:
```.cpp
uniform vec3 triangleColor;
```

Inside the .cpp code:
```.cpp
GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);
```

# Pass data from the vertex shader to the fragment shader
