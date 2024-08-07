#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Global Variables
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
	// Initialize GLFW
	if (!glfwInit())
		return -1;

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Eulerian Grid-Based Fluid Simulation", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return -1;

	

	// Main rendering loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.8f, 0.9f, 0.99f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);




		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}