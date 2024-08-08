#include "headers/options.h"

Options::Options(){}
Options::~Options(){}


void Options::setOptions() {
	;
}


// Process User Input
void Options::processInput(GLFWwindow* window)
{
	// Close window (ESC)
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
