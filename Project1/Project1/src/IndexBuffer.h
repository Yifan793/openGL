#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID;//不论是创建一个buffer、texture、array，都会返回的唯一标识
	unsigned int m_Count;//多少个indices

public:
	IndexBuffer(const unsigned int* data, unsigned int count); //这个系列中，如果有6个数字，size指的是24(4*6)，count指的是6
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline unsigned int GetCount() const { return m_Count; }
};