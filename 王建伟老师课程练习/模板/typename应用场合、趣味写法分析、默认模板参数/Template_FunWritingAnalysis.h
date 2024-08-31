#pragma once

/// <summary>
/// 趣味写法分析
/// 函数指针、可调用对象（解释为:重载类的()符号）做函数模板参数
/// </summary>
namespace Template_FunWritingAnalysis_NameSpace
{
	//别名
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
	/// 求和函数
	/// </summary>
	/// <param name="_X"></param>
	/// <param name="_Y"></param>
	/// <returns></returns>
	int Add(int _X, int _Y);

	/// <summary>
	/// 回调函数
	/// </summary>
	/// <typeparam name="T02"></typeparam>
	/// <typeparam name="T01"></typeparam>
	/// <param name="_X"></param>
	/// <param name="_Y"></param>
	/// <param name="_Func"></param>
	/// <returns></returns>
	template<typename T01, typename T02>
	int CaculateFunc(T01 _X, T01 _Y, T02 _Func);

	//测试函数
	void Test01();
}