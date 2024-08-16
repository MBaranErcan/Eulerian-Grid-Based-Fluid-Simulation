#pragma once

#include <GLFW/glfw3.h>

// Non-functional class, will be implemented in the future to add options to the simulator.
class Options
{
public:
    Options();
    ~Options();

    void setOptions();
    void processInput(GLFWwindow* window);
};