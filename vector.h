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
		//������
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator cbegin()const	//Ȩ����С
		{
			return _start;
		}
		const_iterator cend()const
		{
			return _finish;
		}
		//��ʵ����ķ����������������ģ���Ϊ���������++����ǰ
		reverse_iterator rbegin()
		{
			return _finish - 1;
		}
		reverse_iterator rend()
		{
			return _start - 1;
		}

		//���캯��
		//�޲ι���
		vector() :_start(nullptr), _finish(nullptr), end_of_storage(nullptr) {}

		//����������(��ģ��+����ģ��)
		///Ϊʲô����Ҫ����һ��ģ�����InputIterator����Ϊ���ﹹ�캯����ֹ���Խ���vector����ĵ������������Խ��ձ�������ĵ�����
		template<class InputIterator>
		vector(InputIterator first, InputIterator last) :
			_start(nullptr), _finish(nullptr), end_of_storage(nullptr)
		{
			while (first != last)
			{
				push_back(*first);		//����new��push_back()�Ѿ����������
				first++;
			}
		}

		/*�������죺ԭд��
		vector(vector<T>& vtr)
		{
			_start = new T[vtr.capacity()];
			_finsh = _start + vtr.size();
			end_of_storage = _start + vtr.capacity();

			memcpy(_start, vtr._start, vtr.size());
			//ʹ��memcpy�����bug��
			memcpy�ǰ��ֽڿ��������������������ô����������⣬����������Զ������ͣ���string��
			��ôÿ�ο������ǰѶ�Ӧ��_strָ�뿽����ȥ�ˣ������ͻ����һ����ַ�������ε����⣬���³������

			//����ʹ��string��ĸ�ֵ��������ر���bug
			for (size_t i = 0; i < vtr.size(); i++)
			{
				_start[i] = vtr._start[i];		//���������string�࣬��ô����str1 = str2
			}
		}	*/

		//�ִ�д��
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
			swap(tmp);		//����ʱ�ռ佻�����ݣ������������tmp���٣���������������ԭ����
		}

		//��������
		~vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _finish = end_of_storage = nullptr;
			}
		}

		//operator=()
		vector<T>& operator=(vector<T> vtr)		//��ֵ�����Ǵ�����
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
		const T& operator[](size_t pos)const		//ֻ��
		{
			assert(pos < size());
			return *(_start + pos);
		}

		T& operator[](size_t pos)		//�ɶ���д
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
			//ǰ��˵��int i(10)���ᱨ������������԰�int����һ���࣬����int()�����޲ι��캯�������ʼ��ֵΪ0
			//����T()����һ�����͵ĳ�ʼֵ�Ĺ��캯��(������ô���)
		{
			if (n < size())
			{
				_finish = _start + n;
				//*_finish = val;		//���п���
			}
			else
			{
				if (n > capacity())
				{
					reserve(n);
				}
				//memset(_finish, val, n - size());		error��memset�ĵڶ�������ֻ��Ϊint����
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
			//�ж��Ƿ���Ҫ����
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
			_finish--;		//αɾ��
		}

		//insert()
		iterator insert(iterator pos, const T& val)
		{
			assert(pos >= _start && pos <= _finish);		//�����е��ڣ���Ϊ����posλ��ǰ����
			if (size() == capacity())
			{
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				pos = _start + len;			//����������ݵ���posֵ���ˣ���������Ҫ����
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
		//��string��һ��
		iterator _start;		//��ʼָ��
		iterator _finish;		//���һ�����ݵ���һλ��ָ��
		iterator end_of_storage;//�������λ�õ���һ��λ�õ�ָ��
	};
}
