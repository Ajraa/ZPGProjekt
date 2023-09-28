#include "Callback.h"
void Callback::error_callback(int error, const char* description) {
	fputs(description, stderr); 
}

void Callback::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Callback::window_focus_callback(GLFWwindow* window, int focused)
{
	printf("window_focus_callback \n");
}

void Callback::window_iconify_callback(GLFWwindow* window, int iconified
) {
	printf("window_iconify_callback \n"); 
}

void Callback::window_size_callback(GLFWwindow* window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Callback::cursor_callback(GLFWwindow* window, double x, double y)
{
	printf("cursor_callback \n"); 
}

void Callback::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

