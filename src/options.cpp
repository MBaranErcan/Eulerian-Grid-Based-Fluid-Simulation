#include "headers/Options.h"

Options::Options() {}
Options::~Options() {}

void Options::setOptions() {
	// Placeholder for future implementation
}

void Options::processInput(GLFWwindow* window) {
	// Close window (ESC)
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
