#pragma once
#include <iostream>
#include <vector>
using namespace std;

//priority_queue��ģ��ʵ��
namespace yw
{
	//�º���
	template<class T>
	struct less			//���
	{
		bool operator()(const T& x, const T& y)
		{
			return x < y;
		}
	};

	template<class T>		//С��
	struct greater
	{
		bool operator()(const T& x, const T& y)
		{
			return x > y;
		}
	};

	//ģ���ػ���������Զ�������(����������)
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
			_con(first, last)		//�Ȱ�����¼��_con
		{
			//����
			for (size_t i = (_con.size() - 1 - 1) / 2; i >= 0; i--)
			{
				adjust_down(i);		//���µ�������
			}
		}

	private:
		void adjust_down(size_t parent)
		{
			Compare cmp;
			size_t child = parent * 2 + 1;
			while (child < _con.size())		//û�г�����߽�
			{
				//if(child + 1 < _con.size() && _con[child] < _con[child + 1])
				if (child + 1 < _con.size() && cmp(_con[child], _con[child + 1]))	//�º�������
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
			adjust_up(_con.size() - 1);		//������������ϵ���
		}

	private:		//�����ڲ��ĺ�����װ����
		void adjust_up(size_t child)
		{
			Compare cmp;
			size_t parent = (child - 1) / 2;
			while (child > 0)
			{
				//���ﲻ�ú����ӱȽϣ���Ϊ��ֻҪ��parent����ֵ����
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
			//ɾ��ʱ����ֱ��ɾ���Ӷ�Ԫ�أ������ӻὫ���е�˳��ȫ������

			std::swap(_con[_con.size() - 1], _con[0]);	//�ȶӶ�Ԫ�غ����һ��Ԫ�ؽ���
			_con.pop_back();		//βɾ
			adjust_down(0);			//���µ����ѽṹ
		}

		const T& top() const
		{
			return _con[0];			//����ֵ��Ȼ�����ã������ܱ��޸�
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