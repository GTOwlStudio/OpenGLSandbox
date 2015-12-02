// Version du GLSL

#version 330 core


// Entrée Shader

in vec3 in_Vertex;
in vec3 in_Color;

uniform mat4 projection;
uniform mat4 modelview;

// Fonction main

out vec3 color;

void main()
{
    // Position finale du vertex
    gl_Position = projection * modelview * vec4(in_Vertex, 1.0);
	
	color = in_Color;
	
}
