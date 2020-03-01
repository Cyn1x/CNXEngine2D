#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

class Shader
{
private:
	GLuint m_ShaderProgramID;
	std::string m_VertexShaderFilePath;
	std::string m_FragmentShaderFilePath;
	std::vector<GLfloat> m_UniformFloats;
	std::unordered_map<std::string, GLint> m_UniformLocationCache;
public:
	Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	~Shader();

	void Bind();
	void UnBind();
	void SetUniform1f(const std::string& name, GLfloat value);
	void SetUniform2f(const std::string& name, GLfloat value);
	void SetUniform3f(const std::string& name, GLfloat value);
	void SetUniform4f(const std::string& name, GLfloat value);
private:
	std::string ParseShader(const std::string& filepath);
	GLuint CreateShader(const std::string& vertextShader, const std::string& fragmentShader);
	GLuint CompileShader(GLuint type, const std::string& source);
	GLuint getUniformLocation(const std::string& name);
};
