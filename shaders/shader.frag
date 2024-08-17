#version 460 core

out vec4 FragColor;

uniform float density;

//uniform vec3 colorLowDensity;
//uniform vec3 colorHighDensity;

void main()
{
    FragColor = vec4(1.0, 1.0-density, 1.0-density, 1.0); // Red based on density
}