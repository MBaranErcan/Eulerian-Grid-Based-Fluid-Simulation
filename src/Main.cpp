#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "headers/constants.h"
#include "headers/options.h"


int main()
{
	if (!glfwInit()) return -1;

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Eulerian Grid-Based Fluid Simulation", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return -1;

	// Instances
	Options options;

	// Main rendering loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.8f, 0.9f, 0.99f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		options.processInput(window);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}