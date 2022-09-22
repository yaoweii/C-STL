#pragma once
#include <iostream>
#include <deque>
using namespace std;

//stack的模拟实现
namespace yw
{
	template<class T, class Container = deque<T>>
	class stack
	{
	public:
		//不用写构造函数，用系统默认生成的即可(这里会调用底层Container的构造函数)
		//因为stack只能从栈顶取元素，不支持遍历，所以没有迭代器

		void push(const T& val)
		{
			_con.push_back(val);
		}

		void pop()
		{
			_con.pop_back();
		}

		const T& top() const	//top返回的值不能修改其本身栈的数据
		{
			return _con.back();
		}

		bool empty() const
		{
			return _con.empty();
		}

		size_t size() const
		{
			return _con.size();
		}
	private:
		Container _con;
	};
}


//queue的模拟实现
namespace yw
{
	template<class T, class Container = deque<T>>
	class queue
	{
	private:
		Container _con;
	public:
		bool empty() const
		{
			return _con.empty();
		}

		size_t size() const
		{
			return _con.size();
		}

		const T& front() const
		{
			return _con.front();
		}

		T& front()
		{
			return _con.front();
		}

		T& back()
		{
			return _con.back();
		}

		const T& back() const
		{
			return _con.back();
		}

		void push(const T& val)
		{
			_con.push_back(val);
		}

		void pop()
		{
			_con.pop_front();
			//vector不支持push_front、pop_front，所以不能用于queue的适配器
		}
	};
}


