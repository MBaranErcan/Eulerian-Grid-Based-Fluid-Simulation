#version 460 core

out vec4 FragColor;

const int SIZE = 70;

uniform float density[SIZE * SIZE];
uniform float velocityX[SIZE * SIZE];
uniform float velocityY[SIZE * SIZE];

uniform vec3 colorLowDensity;
uniform vec3 colorHighDensity;

void main()
{
	vec2 fragPos = gl_FragCoord.xy; // get the current fragment's position
	int x = int(fragPos.x);
	int y = int(fragPos.y);
	int index = x + y * SIZE;

	// Get density
	float d = density[index];

	// Get velocity
	vec2 v = vec2(velocityX[index], velocityY[index]);

	// Map density to color
	vec3 color = mix(colorLowDensity, colorHighDensity, d);
		
	// Map velocity to color
//	color = mix(color, vec3(1.0, 0.0, 0.0), length(v) * 0.1);

	FragColor = vec4(color, 1.0);
}