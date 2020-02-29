#pragma once

#include "Renderer.h"

class IndexBuffer
{
private:
	GLuint IndexBufferID;
	GLuint IndexCount;
public:
	IndexBuffer(const GLvoid* data, GLuint size);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
};
