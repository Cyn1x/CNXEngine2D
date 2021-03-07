#include "Application.h"

Application::Application()
{

}

Application::~Application()
{

}

void GLAPIENTRY Application::MessageCallback(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
	    (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
	    type, severity, message);
}
	
void Application::Run()
{
	Window GLFW(800, 600);
	GLFWwindow* window = GLFW.GetWindow();
	
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
	
	GLfloat vertices[] = {
	    -0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
	    -0.5f,  0.5f
	};
	
	GLuint indices[] = {
	    0, 1, 2,
	    2, 3, 0,
	};
	
	GLuint VAO;
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	VertexBuffer* VBO = new VertexBuffer(vertices, 4 * 2 * sizeof(GLfloat));
	IndexBuffer* IBO = new IndexBuffer(indices, 6);
	
	Shader shader(vertexShader, fragmentShader);
	shader.Bind();
	shader.SetUniform4f("vertexColor", 1.0f);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	
	shader.UnBind();
	while (!glfwWindowShouldClose(window))
	{
	    GLFW.ProcessInput(window);
	
	    glClear(GL_COLOR_BUFFER_BIT);
	    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	
	    shader.Bind();
	    shader.SetUniforms("vertexColor", 0.2f, 0.2f, 1.0f, 1.0f);
	    glBindVertexArray(VAO);
	    glDrawElements(GL_LINE_STRIP, 6, GL_UNSIGNED_INT, nullptr);
	
	    glfwSwapBuffers(window);
	    glfwPollEvents();
	}
	
	glDeleteVertexArrays(1, &VAO);
	
	delete VBO, IBO;
}
