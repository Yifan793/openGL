#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID;//�����Ǵ���һ��buffer��texture��array�����᷵�ص�Ψһ��ʶ
	unsigned int m_Count;//���ٸ�indices

public:
	IndexBuffer(const unsigned int* data, unsigned int count); //���ϵ���У������6�����֣�sizeָ����24(4*6)��countָ����6
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline unsigned int GetCount() const { return m_Count; }
};