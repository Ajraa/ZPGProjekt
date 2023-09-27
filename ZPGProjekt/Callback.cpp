#include "Callback.h"

Callback::Callback(GLFWwindow* window)
{
	this->window = window;
}
void Callback::error_callback(int error, const char* description)
{
	fputs(description, stderr); 

}

void Callback::key_callback(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(this->window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Callback::window_focus_callback(int focused)
{
	printf("window_focus_callback \n"); }

void Callback::window_iconify_callback(int iconified)
{
	printf("window_iconify_callback \n"); 
}

void Callback::window_size_callback(int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Callback::cursor_callback(double x, double y)
{ 
	printf("cursor_callback \n");
}

void Callback::button_callback(int button, int action, int mode)
{
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}