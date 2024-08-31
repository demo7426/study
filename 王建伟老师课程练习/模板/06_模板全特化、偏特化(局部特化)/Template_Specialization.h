#pragma once

#include<iostream>

using namespace std;

/// <summary>
/// ģ���ػ�Ŀ¼:
///	(1)��ģ���ػ�
///		(1.1)��ģ��ȫ�ػ�
///			a)����ȫ�ػ�
///			b)�ػ���Ա������������ģ��
///		(1.2)��ģ��ƫ�ػ����ֲ��ػ���
///			a)ģ���������
///			b)ģ�������Χ
/// (2)����ģ���ػ�
///		(2.1)����ģ��ȫ�ػ�
///		(2.2)����ģ��ƫ�ػ�(�������ͨ�������ǹ��ܲ�����)
/// (3)ģ���ػ��汾����λ�ý���
/// </summary>
namespace Template_Specialization_NameSpace
{
	template<typename T, typename U,typename W>
	struct CCaculator
	{
		CCaculator()
		{
			cout << "CCaculator��ģ�巺�ͣ����캯����" << endl;
		}

		T Add(U _X, W _Y)
		{
			cout << "CCaculator��ģ�巺�ͣ�Add()������" << endl;
			return _X + _Y;
		}
	};


	//��ģ�峣��ȫ�ػ�
	template<>
	struct CCaculator<double, int, int>
	{
		CCaculator()
		{
			cout << "CCaculator��ģ��ȫ�ػ������캯����" << endl;
		}

		template<typename T, typename U, typename W>
		T Add(U _X, W _Y)
		{
			cout << "CCaculator��ģ��ȫ�ػ���Add()������" << endl;
			return _X + _Y;
		}
	};

	//��ģ��ȫ�ػ����ػ���Ա������������ģ��
	template<>
	int CCaculator<int, int, int>::Add(int _X, int _Y)
	{
		cout << "CCaculator��ģ��ȫ�ػ����ػ���Ա������Add()������" << endl;
		return _X + _Y;
	}

	//��ģ��ƫ�ػ���ģ���������
	template<typename U>
	struct CCaculator<string, U, string>
	{
		CCaculator()
		{
			cout << "CCaculator��ģ��ƫ�ػ���ģ��������������캯����" << endl;
		}

		string Add(U _X, string _Y)
		{
			cout << "CCaculator��ģ��ƫ�ػ���ģ�����������Add()������" << endl;
			return _X + _Y;
		}
	};

	//��ģ��ƫ�ػ���ģ�������Χ
	template<>
	struct CCaculator<int, int&, int&>
	{
		template<typename T, typename U, typename W>
		T Add(U _X, W _Y)
		{
			cout << "CCaculator��ģ��ƫ�ػ���ģ�������Χ��Add()������" << endl;
			return _X + _Y;
		}
	};

	//����ģ��
	template<typename T, typename U, typename W >
	T Mul(U _X, W _Y)
	{
		cout << "����ģ�巺�ͣ�Mul()������" << endl;
		return _X * _Y;
	}

	//����ģ��ȫ�ػ�
	template<>
	double Mul(double _X, int _Y)
	{
		cout << "����ģ��ȫ�ػ���Mul()������" << endl;
		return _X * _Y;
	}

	//����ģ��û��ƫ�ػ����ܣ��������ͨ�������ǹ��ܲ�����
	template<typename U>
	int Mul(U _X, double _Y)
	{
		cout << "����ģ��ƫ�ػ���Mul()������" << endl;
		return _X * _Y;
	}

	//���Ժ���
	void Test01();
}