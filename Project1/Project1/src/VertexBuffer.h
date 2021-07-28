#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;//不论是创建一个buffer、texture、array，都会返回的唯一标识
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;
};