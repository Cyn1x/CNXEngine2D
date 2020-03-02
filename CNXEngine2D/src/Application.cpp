#include "Application.h"

Application::Application()
{

}

Application::~Application()
{

}

void Application::Run()
{
    Window GLFW(800, 600);
    GLFWwindow* window = GLFW.GetWindow();

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

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

    Shader shader("assets/shaders/VertexShader.glsl", "assets/shaders/FragmentShader.glsl");
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
        shader.SetUniform1f("vertexColor", 0.2f);
        shader.SetUniform2f("vertexColor", 0.2f);
        shader.SetUniform3f("vertexColor", 1.0f);
        shader.SetUniform4f("vertexColor", 1.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_LINE_STRIP, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);

    delete VBO, IBO;
}
