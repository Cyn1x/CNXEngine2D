#pragma once

#include <glad/glad.h>

class VertexArray
{
private:
	GLuint m_VertexArrayID;
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
};
