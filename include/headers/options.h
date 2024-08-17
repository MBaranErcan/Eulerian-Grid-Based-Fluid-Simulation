#pragma once

#include <GLFW/glfw3.h>

#include "headers/Constants.h"
#include "headers/Physics.h"
#include <iostream>

// Non-functional class, will be implemented in the future to add options to the simulator.
class Options
{
private:
    static bool isWireframe;


public:
    Options(GLFWwindow* window);
    ~Options();

    void setOptions(GLFWwindow* window);

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);


};