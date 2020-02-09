#pragma once

#include "Renderer.h"

class IndexBuffer
{
private:
	GLuint m_RendererID;
	GLuint m_Count;
public:
	IndexBuffer(const GLvoid* data, GLuint size);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
};
