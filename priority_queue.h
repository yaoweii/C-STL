#pragma once
#include <iostream>
#include <vector>
using namespace std;

//priority_queue的模拟实现
namespace yw
{
	//仿函数
	template<class T>
	struct less			//大堆
	{
		bool operator()(const T& x, const T& y)
		{
			return x < y;
		}
	};

	template<class T>		//小堆
	struct greater
	{
		bool operator()(const T& x, const T& y)
		{
			return x > y;
		}
	};

	//模板特化——针对自定义类型(比如日期类)
	class Date
	{
		friend 	ostream& operator<<(ostream& out, Date& d);
	public:
		Date(int year, int month, int day) :
			year(year), month(month), day(day)
		{}

		bool operator<(const Date& d) const
		{
			return year < d.year ||
				(year == d.year && month < d.month) ||
				(year == d.year && month == d.month && day < d.day);
		}
		bool operator>(const Date& d) const
		{
			return year > d.year ||
				(year == d.year && month > d.month) ||
				(year == d.year && month == d.month && day > d.day);
		}
	private:
		int day;
		int month;
		int year;
	};

	ostream& operator<<(ostream& out, Date& d)
	{
		cout << d.year << '/' << d.month << '/' << d.day << '/';
		return out;
	}

	template<>
	struct less<Date*>
	{
		bool operator()(const Date*& x, const Date*& y)
		{
			return (*x) < (*y);
		}
	};


	template<>
	struct greater<Date*>
	{
		bool operator()(const Date*& x, const Date*& y)
		{
			return *x > *y;
		}
	};

	template<class T, class Container = vector<T>, class Compare = less<T>>
	class priority_queue
	{
	private:
		Container _con;
	public:
		priority_queue() {}

		template<class InputIterator>
		priority_queue(InputIterator first, InputIterator last) :
			_con(first, last)		//先把数据录入_con
		{
			//建堆
			for (size_t i = (_con.size() - 1 - 1) / 2; i >= 0; i--)
			{
				adjust_down(i);		//向下调整建堆
			}
		}

	private:
		void adjust_down(size_t parent)
		{
			Compare cmp;
			size_t child = parent * 2 + 1;
			while (child < _con.size())		//没有出数组边界
			{
				//if(child + 1 < _con.size() && _con[child] < _con[child + 1])
				if (child + 1 < _con.size() && cmp(_con[child], _con[child + 1]))	//仿函数调用
				{
					child += 1;
				}
				if (cmp(_con[parent], _con[child]))
				{
					std::swap(_con[parent], _con[child]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
					break;
			}
		}

	public:
		void push(const T& val)
		{
			_con.push_back(val);
			adjust_up(_con.size() - 1);		//插入的数据向上调整
		}

	private:		//将类内部的函数封装起来
		void adjust_up(size_t child)
		{
			Compare cmp;
			size_t parent = (child - 1) / 2;
			while (child > 0)
			{
				//这里不用和左孩子比较，因为堆只要求parent是最值即可
				if (cmp(_con[parent], _con[child]))
				{
					std::swap(_con[parent], _con[child]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
					break;
			}
		}

	public:
		void pop()
		{
			//删除时不能直接删除队顶元素，这样子会将堆中的顺序全部打乱

			std::swap(_con[_con.size() - 1], _con[0]);	//先队顶元素和最后一个元素交换
			_con.pop_back();		//尾删
			adjust_down(0);			//向下调整堆结构
		}

		const T& top() const
		{
			return _con[0];			//返回值虽然是引用，但不能被修改
		}

		size_t size()
		{
			return _con.size();
		}

		bool empty()
		{
			return _con.empty();
		}
	};
}