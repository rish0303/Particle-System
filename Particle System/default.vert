#version 330 core

//Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;


// Outputs the color for the Fragment Shader
out vec3 color;


uniform mat4 world;
uniform mat4 projection;
uniform mat4 view;


void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = projection * world * vec4(aPos, 1);
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
}