//�ļ�������
//      ʵ��һ����д������ģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/2/20
//�޸ļ�¼��
//      2024/2/20     �½�
#pragma once

class CBuffer
{
public:
	CBuffer() = delete;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="_Capcity">��������С</param>
	CBuffer(int _Capcity);
	~CBuffer();

	// �ӿͻ����ļ�����������������ȡ����
	int SocketRead(int _Fd);

	// ��д�����������ݷ��͵��ͻ���
	int SocketSend(int _Fd);

	// ��ȡ�����http���з����ڴ�λ��
	char* GetCRLFNearestPtr();

	// �򻺳���д�����ݣ�����_Size������ֹд�����������ʱ������'\0'�������������д��ȱʧ�������
	int AppendString(const char* _pData, int _Size);

	// �򻺳���д���ַ���
	int AppendString(const char* _pData);

	inline char* GetStartPtr()
	{
		return m_pchStartPtr;
	}
	
	inline int GetReadPos()
	{
		return m_nReadPos;
	}
	
	inline int SetReadPos(int _ReadPos)
	{
		if (_ReadPos < 0)
			return -1;

		m_nReadPos = _ReadPos;
		return 0;
	}

	//��⻺������������ȡ�Ŀռ��С
	inline int GetBufferContinuousReadSize()
	{
		//��Ϊ�ڼ��д��ռ��Ƿ���ʱ��ͨ���ڴ��ƶ��������ݣ���֤��д��λ����Զ�Ǵ��ڶ�ȡλ�õģ����Է���ֱֵ�������
		return this->m_nWritePos - this->m_nReadPos;
	}

private:
	// ��⻺�����Ŀ�д��ռ��С�Ƿ�����д�����ݴ�С�����������������
	int CheckBufferWriteSize(int _WriteSize);

	//��⻺����������д��Ŀռ��С
	inline int GetBufferContinuousWriteSize()
	{
		return this->m_nCapacity - this->m_nWritePos;
	}

	
private:
	int m_nCapacity;				//����
	char* m_pchStartPtr;			//��������ʼ��ַ
	int m_nReadPos;				//��λ��
	int m_nWritePos;				//дλ��
};
