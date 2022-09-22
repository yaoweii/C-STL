#pragma once
#include <iostream>
#include <deque>
using namespace std;

//stack��ģ��ʵ��
namespace yw
{
	template<class T, class Container = deque<T>>
	class stack
	{
	public:
		//����д���캯������ϵͳĬ�����ɵļ���(�������õײ�Container�Ĺ��캯��)
		//��Ϊstackֻ�ܴ�ջ��ȡԪ�أ���֧�ֱ���������û�е�����

		void push(const T& val)
		{
			_con.push_back(val);
		}

		void pop()
		{
			_con.pop_back();
		}

		const T& top() const	//top���ص�ֵ�����޸��䱾��ջ������
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


//queue��ģ��ʵ��
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
			//vector��֧��push_front��pop_front�����Բ�������queue��������
		}
	};
}


