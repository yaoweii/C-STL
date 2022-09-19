#pragma once
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstring>
#include <cstdlib>
using namespace std;
namespace yw
{
	template <class T>
	class vector {
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		typedef T* reverse_iterator;
		//迭代器
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator cbegin()const	//权限缩小
		{
			return _start;
		}
		const_iterator cend()const
		{
			return _finish;
		}
		//其实这里的反向迭代器是有问题的，因为反向迭代器++是向前
		reverse_iterator rbegin()
		{
			return _finish - 1;
		}
		reverse_iterator rend()
		{
			return _start - 1;
		}

		//构造函数
		//无参构造
		vector() :_start(nullptr), _finish(nullptr), end_of_storage(nullptr) {}

		//迭代器构造(类模板+函数模板)
		///为什么这里要设置一个模板参数InputIterator？因为这里构造函数不止可以接收vector本身的迭代器，还可以接收别的容器的迭代器
		template<class InputIterator>
		vector(InputIterator first, InputIterator last) :
			_start(nullptr), _finish(nullptr), end_of_storage(nullptr)
		{
			while (first != last)
			{
				push_back(*first);		//不用new，push_back()已经解决该问题
				first++;
			}
		}

		/*拷贝构造：原写法
		vector(vector<T>& vtr)
		{
			_start = new T[vtr.capacity()];
			_finsh = _start + vtr.size();
			end_of_storage = _start + vtr.capacity();

			memcpy(_start, vtr._start, vtr.size());
			//使用memcpy会存在bug：
			memcpy是按字节拷贝，如果是内置类型那么不会存在问题，但是如果是自定义类型，如string类
			那么每次拷贝都是把对应的_str指针拷贝过去了，这样就会存在一个地址析构两次的问题，导致程序崩溃

			//可以使用string类的赋值运算符重载避免bug
			for (size_t i = 0; i < vtr.size(); i++)
			{
				_start[i] = vtr._start[i];		//如果这里是string类，那么就是str1 = str2
			}
		}	*/

		//现代写法
		void swap(vector<T>& vtr)
		{
			std::swap(_start, vtr._start);
			std::swap(_finish, vtr._finish);
			std::swap(end_of_storage, vtr.end_of_storage);
		}

		vector(vector<T>& vtr) :
			_start(nullptr), _finish(nullptr), end_of_storage(nullptr)
		{
			vector<T> tmp(vtr.begin(), vtr.end());
			swap(tmp);		//和临时空间交换数据，函数运行完后tmp销毁，但是里面数据是原来的
		}

		//析构函数
		~vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _finish = end_of_storage = nullptr;
			}
		}

		//operator=()
		vector<T>& operator=(vector<T> vtr)		//传值，不是传引用
		{
			swap(vtr);
			return *this;
		}

		size_t size()
		{
			return _finish - _start;
		}

		size_t capacity()
		{
			return end_of_storage - _start;
		}

		//operator[]()
		const T& operator[](size_t pos)const		//只读
		{
			assert(pos < size());
			return *(_start + pos);
		}

		T& operator[](size_t pos)		//可读可写
		{
			assert(size() > pos);
			return _start[pos];
		}

		//reserve()
		void reserve(size_t n)
		{
			if (capacity() < n)
			{
				T* tmp = new T[n];
				size_t sz = size();
				if (_start)
				{
					for (size_t i = 0; i < sz; i++)
					{
						tmp[i] = _start[i];
					}
					delete[] _start;
				}
				_start = tmp;
				_finish = _start + sz;
				end_of_storage = _start + n;
			}
		}

		//resize()
		void resize(size_t n, const T& val = T())
			//前面说过int i(10)不会报错，所以这里可以把int看成一个类，所以int()就是无参构造函数，其初始化值为0
			//所以T()就是一个类型的初始值的构造函数(可以这么理解)
		{
			if (n < size())
			{
				_finish = _start + n;
				//*_finish = val;		//可有可无
			}
			else
			{
				if (n > capacity())
				{
					reserve(n);
				}
				//memset(_finish, val, n - size());		error，memset的第二个参数只能为int类型
				for (iterator it = _finish; it != _start + n; ++it)
				{
					*it = val;
				}
				_finish = _start + n;
			}
		}

		//push_back()
		void push_back(const T& val)
		{
			//判断是否需要扩容
			if (_finish == end_of_storage)
			{
				reserve(capacity() == 0 ? 4 : capacity() * 2);
			}
			*_finish++ = val;
		}

		//pop_back()
		void pop_back()
		{
			assert(_start != _finish);
			_finish--;		//伪删除
		}

		//insert()
		iterator insert(iterator pos, const T& val)
		{
			assert(pos >= _start && pos <= _finish);		//可以有等于，因为是在pos位置前插入
			if (size() == capacity())
			{
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				pos = _start + len;			//可能异地扩容导致pos值变了，所以这里要修正
			}
			for (iterator it = _finish; it != pos; it--)
			{
				T tmp = *(it - 1);
				*it = tmp;
			}
			*pos = val;
			++_finish;
			return pos;
		}

		//erase()
		iterator erase(iterator pos)
		{
			assert(pos >= _start && pos < _finish);
			for (iterator it = pos; it != _finish - 1; it++)
			{
				*it = *(it + 1);
			}
			_finish--;
			return pos;
		}
	private:
		//和string不一样
		iterator _start;		//起始指针
		iterator _finish;		//最后一个数据的下一位的指针
		iterator end_of_storage;//最大容量位置的下一个位置的指针
	};
}
