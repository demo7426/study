#pragma once

/// <summary>
/// 类成员函数模板
/// </summary>
namespace Template_ClassMemberFuncTempalte_NameSpace
{
	template<typename T01>
	class CStudent
	{
	public:
		CStudent();
		~CStudent();

		typedef T01* iterator;
		
		/// <summary>
		/// 根据学生Id号获取学生名称
		/// </summary>
		/// <typeparam name="T02"></typeparam>
		/// <param name="_Id">Id号</param>
		/// <returns></returns>
		template<typename T02>
		T02 GetName(const size_t& _Id)const;
	private:

	};

	template<typename T01>
	CStudent<T01>::CStudent()
	{
	}

	template<typename T01>
	CStudent<T01>::~CStudent()
	{
	}

	template<typename T01>
	template<typename T02>
	T02 CStudent<T01>::GetName(const size_t& _Id)const
	{

	}

	template<typename T>
	T Calculator_Add(const T& _X, const T& _Y)
	{
		return _X + _Y;
	}
}