#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;//�����Ǵ���һ��buffer��texture��array�����᷵�ص�Ψһ��ʶ
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;
};