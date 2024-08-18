#include "headers/Options.h"

extern Physics physics;

bool Options::isWireframe = false;

Options::Options(GLFWwindow* window) {
	setOptions(window);
}

Options::~Options() {}

void Options::setOptions(GLFWwindow* window) {
	try {
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, Options::framebuffer_size_callback);
		glfwSetCursorPosCallback(window, Options::mouse_callback);
//		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetKeyCallback(window, Options::key_callback);

		isWireframe = false;
	}
	catch (const std::exception& e) {
		std::cerr << "Exception in setOptions: " << e.what() << std::endl;
	}
}


void Options::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}


void Options::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
		glfwSetWindowShouldClose(window, true);
	}

	// Change to polygon mode to see the grid ('P')
	if (key == GLFW_KEY_P && action == GLFW_RELEASE) {
		isWireframe = !isWireframe;
		glPolygonMode(GL_FRONT_AND_BACK, isWireframe ? GL_LINE : GL_FILL);
	}

    // Reset the grid ('R')
    if (key == GLFW_KEY_R && action == GLFW_RELEASE) {
        physics.reset();
    }
}

void Options::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    static float lastX = xpos;
    static float lastY = ypos;
    int gridX = -1;
    int gridY = -1;

    // Clamp the mouse position to the window borders
    xpos = std::max(0.0, std::min(xpos, static_cast<double>(SCR_WIDTH)));
    ypos = std::max(0.0, std::min(ypos, static_cast<double>(SCR_HEIGHT)));

    // Update the mouse position if it was clamped
    if (xpos != lastX || ypos != lastY) {
        glfwSetCursorPos(window, xpos, ypos);
    }

    gridX = static_cast<int>(xpos / SCR_WIDTH * N);
    gridY = static_cast<int>((SCR_HEIGHT - ypos) / SCR_HEIGHT * N);

    // 1: left border, N: right border
    if (gridX >= 1 && gridX <= N && gridY >= 1 && gridY <= N)
    {
        // Add fluid velocity (Left Click + Drag)
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            for (int i = -addRadius; i <= addRadius; ++i)
            {
                for (int j = -addRadius; j <= addRadius; ++j)
                {
                    int neighborX = gridX + i;
                    int neighborY = gridY + j;
                    if (neighborX >= 1 && neighborX <= N && neighborY >= 1 && neighborY <= N)
                    {
                        // Check if the neighbor is within the circular radius
                        if (sqrt(i * i + j * j) <= addRadius)
                        {
                            int neighborIndex = IX(neighborX, neighborY);
                            double forceX = xpos - lastX;
                            double forceY = lastY - ypos;
                            physics.u[neighborIndex] += forceX * addForce;
                            physics.u[neighborIndex] = std::min(physics.u[neighborIndex], 1.0f);
                            physics.v[neighborIndex] += forceY * addForce;
                            physics.v[neighborIndex] = std::min(physics.v[neighborIndex], 1.0f);
                        }
                    }
                }
            }
        }
        // Add fluid density (Right Click + Drag)
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            for (int i = -addRadius; i <= addRadius; ++i)
            {
                for (int j = -addRadius; j <= addRadius; ++j)
                {
                    int neighborX = gridX + i;
                    int neighborY = gridY + j;
                    if (neighborX >= 1 && neighborX <= N && neighborY >= 1 && neighborY <= N)
                    {
                        // Check if the neighbor is within the circular radius
                        if (sqrt(i * i + j * j) <= addRadius)
                        {
                            int neighborIndex = IX(neighborX, neighborY);
                            physics.dens[neighborIndex] += addDensity;
                            physics.dens[neighborIndex] = std::min(physics.dens[neighborIndex], 1.0f);
                        }
                    }
                }
            }
        }
        // Add fluid density source (Middle Click)
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
            for (int i = -addRadius; i <= addRadius; ++i)
            {
                for (int j = -addRadius; j <= addRadius; ++j)
                {
                    int neighborX = gridX + i;
					int neighborY = gridY + j;
                    if (neighborX >= 1 && neighborX <= N && neighborY >= 1 && neighborY <= N)
                    {
                        // Check if the neighbor is within the circular radius
                        if (sqrt(i * i + j * j) <= addRadius)
                        {
                            int neighborIndex = IX(neighborX, neighborY);
                            physics.s[neighborIndex] += 1;
                            physics.s[neighborIndex] = std::min(physics.s[neighborIndex], 1.0f);
                        }
                    }
                }
            }
		}

    }
    lastX = xpos;
    lastY = ypos;
}
