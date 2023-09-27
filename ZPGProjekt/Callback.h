#pragma once
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
class Callback
{
public:
	Callback(GLFWwindow* window);
	void error_callback(int error, const char* description);
	void key_callback(int key, int scancode, int action, int mods);
	void window_focus_callback(int focused);
	void window_iconify_callback(int iconified);
	void window_size_callback(int width, int height);
	void cursor_callback(double x, double y);
	void button_callback(int button, int action, int mode);
private:
	GLFWwindow* window;
}; 

