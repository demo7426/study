/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	Singleton.h
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.05.06
��  ��: ʵ��һ������ģ����
��  ע:
�޸ļ�¼:

  1.  ����: 2025.05.06
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.1.0

*************************************************/

#pragma once

#include <iostream>
#include <memory>

template<typename T>
class CSingleton		//����ģ����
{
protected:
	CSingleton() = default;
	CSingleton(const CSingleton<T>&) = delete;
	CSingleton& operator = (const CSingleton<T>&) = delete;

public:
	~CSingleton()		//��֤���������������������
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/// <summary>
	/// ��ȡʵ��������
	/// </summary>
	/// <returns></returns>
	static std::shared_ptr<T> GetInstance()
	{
		static std::once_flag tOnceFlag;

		//std::call_once�����̰߳�ȫ�����ڲ��м�������������
		std::call_once(tOnceFlag, [&]() {
			m_pcInstance = std::shared_ptr<T>(new T);
			});

		return m_pcInstance;
	}

private:
	static std::shared_ptr<T> m_pcInstance;
};

template<typename T>
std::shared_ptr<T> CSingleton<T>::m_pcInstance = nullptr;
