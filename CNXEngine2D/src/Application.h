#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Window.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Application
{
private:

public:
	Application();
	~Application();

	void Run();
};
