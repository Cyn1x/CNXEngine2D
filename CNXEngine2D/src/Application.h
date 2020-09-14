#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Window.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define vertexShader "assets/shaders/VertexShader.glsl"
#define fragmentShader "assets/shaders/FragmentShader.glsl"

class Application
{
private:

public:
	Application();
	~Application();

	void Run();
	static void GLAPIENTRY MessageCallback(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam);
};
