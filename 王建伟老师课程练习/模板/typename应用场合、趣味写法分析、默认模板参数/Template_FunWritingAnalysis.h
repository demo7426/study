#pragma once

/// <summary>
/// Ȥζд������
/// ����ָ�롢�ɵ��ö��󣨽���Ϊ:�������()���ţ�������ģ�����
/// </summary>
namespace Template_FunWritingAnalysis_NameSpace
{
	//����
	typedef int FuncTypename(int _X, int _Y);

	class CAdd
	{
	public:
		CAdd();
		CAdd(const CAdd& _Add);
		~CAdd();

		int operator ()(int _X, int _Y)const
		{
			return _X + _Y;
		}
	private:

	};

	/// <summary>
	/// ��ͺ���
	/// </summary>
	/// <param name="_X"></param>
	/// <param name="_Y"></param>
	/// <returns></returns>
	int Add(int _X, int _Y);

	/// <summary>
	/// �ص�����
	/// </summary>
	/// <typeparam name="T02"></typeparam>
	/// <typeparam name="T01"></typeparam>
	/// <param name="_X"></param>
	/// <param name="_Y"></param>
	/// <param name="_Func"></param>
	/// <returns></returns>
	template<typename T01, typename T02>
	int CaculateFunc(T01 _X, T01 _Y, T02 _Func);

	//���Ժ���
	void Test01();
}