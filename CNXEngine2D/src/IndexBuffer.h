#pragma once

#include "Renderer.h"

class IndexBuffer
{
private:
	GLuint m_IndexBufferID;
	GLuint m_IndexCount;
public:
	IndexBuffer(const GLvoid* data, GLuint size);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
};
