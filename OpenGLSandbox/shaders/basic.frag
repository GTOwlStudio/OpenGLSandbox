// Version du GLSL

#version 330 core

//Entree Shader

in vec3 color;
// Sortie Shader

out vec4 frag_Color;


// Fonction main

void main()
{
    // Couleur finale du pixel
    //frag_Color = vec4(color, 1.0);
	frag_Color = vec4(1.0, 1.0, 1.0, 1.0);
}
