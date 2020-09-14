#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
private:
	GLuint m_ScreenWidth;
	GLuint m_ScreenHeight;
	GLFWwindow* m_Window;
public:
	Window(GLint width, GLint height);
	~Window();

	void ProcessInput(GLFWwindow* window);
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	GLFWwindow* GetWindow();
private:
	GLint CreateWindow();
	GLint InitGlad();
};
