#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "headers/Shader.h"
#include "headers/Constants.h"
#include "headers/Options.h"
#include "headers/Physics.h"


// Physics
Physics physics;

// Time step
float dt = 0.0f;
float lastFrame = 0.0f;


int main()
{
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Eulerian Grid-Based Fluid Simulation", NULL, NULL);
	if (!window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	Options options(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Shader
	Shader shader("shaders/shader.vert", "shaders/shader.frag");
	shader.use();


	float quadVertices[] = {
		// positions
		0.0f, 0.0f, // bottom-left
		0.0f, 1.0f,  // top-left
		1.0f, 1.0f, // top-right
		0.0f, 0.0f, // bottom-left
		1.0f, 1.0f, // top-right
		1.0f, 0.0f, // bottom-right
	};

	unsigned int quadVBO, quadVAO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);

	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); // Positions
	glEnableVertexAttribArray(0);


	// Main rendering loop
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		dt = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.8f, 0.9f, 0.99f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Physics step
		physics.step(dt);

		int i, j, index;
		for (j = 1; j <= N; j++)
		{
			for (i = 1; i <= N; i++)
			{
				index = IX(i, j);

				float x = (float)i / N;
				float y = (float)j / N;

				glUniform1f(glGetUniformLocation(shader.ID, "density"), physics.dens[index]);

				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(2.0f * x - 1.0f, 2.0f * y - 1.0f, 0.0f));
				model = glm::scale(model, glm::vec3(2.0f / N, 2.0f / N, 1.0f));
				glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
