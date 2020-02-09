#pragma once

#include "Renderer.h"

class VertexBuffer
{
private:
	GLuint m_RendererID;
public:
	VertexBuffer(const GLvoid* data, GLuint size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};