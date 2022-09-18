#pragma once 
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
using namespace std;

//string��ģ��ʵ��
namespace yw			//����һ���Լ��������ռ��ֹ��c++������
{
	class string
	{
	private:
		size_t _capacity;		//�ܴ洢��Ч�ַ��ĸ������������ַ�����β\0
		size_t _size;			//��Ч�ַ�����
		char* _str;
	public:
		//�вι���
		//string(const char* = "\0")		//����ʾ��
		//string(const char* = nullptr)		//����ʾ��
		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];		//�࿪��һ������/0
			strcpy(_str, str);
		}

		/*��������
		string(const string& str)
		{
			_size = str._size;
			_capacity = str._capacity;
			_str = new char[str._capacity + 1];
			strcpy(_str, str._str);
		}
		//��ֵ����
		string& operator=(const string& str)
		{
			if (this != &str)	//�����Լ����Լ���ֵ������ԭ��ַ�����仯
			{
				_size = str._size;
				_capacity = str._capacity;
				char* tmp = new char[str._capacity + 1];	//���
				strcpy(tmp, str._str);		//����string.h�Ŀ⺯��(��ϰc���ԣ�)
				delete[] _str;		//ɾ��ԭ���Ŀռ�
				_str = tmp;
			}
			return *this;
		}*/

		//�������ԭ����������͸�ֵ��������ص�д��������д������(����)��

		void swap(string& str)		//��ʵ�����string�����swap�����ӿ�
		{
			std::swap(_str, str._str);		//ʹ��std�����swap�⺯��
			std::swap(_size, str._size);
			std::swap(_capacity, str._capacity);
		}

		string(const string& str) :_str(nullptr), _size(0), _capacity(0)
		{
			string tmp(str._str);	//�Ա�����������ַ����������вι��촴��һ���µ���ʱ����
			swap(tmp);
		}

		string& operator=(string str)	//��Ϊ����ֵ�����Ի���ÿ������촴��һ���βζ���
		{
			swap(str);		//ֱ�ӽ��βκ�ԭ���󽻻�
			return *this;	//������������βλ����٣��������β�ָ�����ԭ����ĵ�ַ
		}

		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		//size()
		size_t size()
		{
			return _size;
		}

		//capacity()
		size_t capacity()
		{
			return _capacity;
		}

		//clear():��ԭ�ַ�����գ������Ϊ�մ�(���ַ�)
		void clear()
		{
			_size = 0;
			_str[0] = '\0';		//αɾ��
		}

		//empty()
		bool empty()
		{
			return _size == 0;
		}

		//operator[](size_t pos)
		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return *(_str + pos);		//str[pos]Ҳ����
		}

		//c_str():����c��ʽ�ַ���
		const char* c_str() const
		{
			return _str;
		}

		//reserve()
		void reserve(size_t n)
		{
			if (_capacity < n)
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;		//�ͷ�ԭ�ռ�
				_str = tmp;
				_capacity = n;
			}
			//�Ѿ����ڻ��ߵ���n�Ͳ�������
		}

		//resize()
		void resize(size_t n, const char& ch = char())
		{
			if (n <= _size)
			{
				_str[n] = '\0';		//���n <= _size����ôֻ��Ҫ��n�����ַ��ĳ�\0����־�ַ����Ľ�β
			}
			else
			{
				if (n > _capacity)		//��Ҫ������
				{
					reserve(n);
				}
				memset(_str + _size, ch, n - _size - 1);		//string.h����ĺ���(��ϰc����!)
				_str[n] = '\0';		//�������ַ�����β��\0
			}
			_size = n;
		}

		//append():�ַ���׷��
		void append(const char* str)
		{
			//���ж��Ƿ���Ҫ����
			if (_capacity < strlen(str) + _size)
			{
				reserve(_size + strlen(str));
			}
			strcpy(_str + _size, str);
			_size = strlen(str) + _size;
		}

		//push_back()
		void push_back(const char& ch)
		{
			if (_capacity == _size)
			{
				reserve(_capacity == 0 ? 2 : _capacity * 2);
			}
			_str[_size++] = ch;
			_str[_size] = '\0';
		}

		//operator+=()
		string& operator+=(const char& ch)
		{
			push_back(ch);
			return *this;
		}

		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}

		//insert()
		string& insert(size_t pos, char ch)
		{
			assert(pos <= _size);		//��Ϊinsert����pos֮ǰ���룬������������е���
			if (_capacity == _size)
			{
				reserve(_capacity == 0 ? 2 : _capacity * 2);
			}
			for (size_t i = _size + 1; i > pos; i--)
			{
				_str[i] = _str[i - 1];
			}
			_str[pos] = ch;
			_size++;
			return *this;
		}

		string& insert(size_t pos, const char* str)
		{
			assert(_size >= pos);
			if (_capacity < _size + strlen(str))
			{
				reserve(_capacity + strlen(str));
			}
			memmove(_str + pos + strlen(str), _str + pos, _size - pos + 1);
			//(_str + pos + strlen(str)��ʾ����ԭ�ַ���ĩβ��\0Ҳ���ǽ�ȥ��)
			strncpy(_str + pos, str, strlen(str));
			//��ϰstring.h��stdlib.h������ĺ���

			_size = _size + strlen(str);
			return *this;
		}
	private:
		static const size_t npos;		//�����ʼ��
		//static const size_t npos = -1;		//Ҳ����
	public:
		//erase():ɾ����posλ�ÿ�ʼ(����posλ��)���n���ַ��������n����pos������ַ���������ôĬ��ɾ������������ַ��������������Ĭ�Ͼ���clear()
		string& erase(size_t pos = 0, size_t n = npos)
		{
			assert(pos < _size);
			if (n == npos || n >= _size - pos)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				for (size_t i = pos; i < pos + n; i++)
				{
					_str[i] = _str[i + n];
				}
				//Ҳ����strcpy(_str + pos, _str + pos + n);
				_size -= n;
			}
			return *this;
		}
		//npos:�������Ϊsize_t�����ֵ��������һЩ֪ʶ��https://mbd.baidu.com/ma/s/fl2sA3T8

		//find()
		size_t find(char ch, size_t pos = 0)
		{
			assert(pos < _size);
			for (size_t i = pos; i < _size; ++i)
			{
				if (_str[i] == ch)
					return i;
			}
			return npos;		//-1
		}

		//find()
		size_t find(const char* str, size_t pos = 0)
		{
			assert(pos < _size);
			const char* ptr = strstr(_str + pos, str);		//string.h�Ŀ⺯��
			if (ptr == nullptr)
			{
				return npos;		//-1
			}
			else return ptr - _str;		//���㣡
		}

		//������(string�ĵ���������һ��char*ָ��������������Ҫ�õ�������begin()��end()����)
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		const_iterator cbegin()const 
		{
			return _str;
		}
		const_iterator cend()const 
		{
			return _str + _size;
		}

		//���������
		friend bool operator==(string& str1, string& str2);
		friend bool operator<(string& str1, string& str2);
		friend bool operator<=(string& str1, string& str2);
		friend bool operator>(string& str1, string& str2);
		friend bool operator>=(string& str1, string& str2);
		friend ostream& operator<<(ostream& out, string& str);
		friend istream& operator>>(istream& in, string& str);
		friend istream& getline(istream& in, string& str);
	};

	//string���⣺
	const size_t string::npos = -1;		//npos����Ϊ-1

	//operator==()
	bool operator==(string& str1, string& str2)
	{
		return strcmp(str1._str, str2._str) == 0;
	}
	//operator<()
	bool operator<(string& str1, string& str2)
	{
		return strcmp(str1._str, str2._str) < 0;
	}
	//operator<=()
	bool operator<=(string& str1, string& str2)
	{
		int ret = strcmp(str1._str, str2._str);
		return ret <= 0;
	}
	//operator>()
	bool operator>(string& str1, string& str2)
	{
		return !(str1 <= str2);
	}
	//operator>=()
	bool operator>=(string& str1, string& str2)
	{
		return !(str1 < str2);
	}

	//cout��cin��getline
	ostream& operator<<(ostream& out, string& str)
	{
		for (auto e : str)		//ʹ��begin()��end()��Χѭ��
		{
			out << e;
		}
		//���ﲻ����cout << str.c_str();

		/*Ҳ�������£�
		for(int i = 0; i < str.size(); i++)
		{
			out << _str[i]
		}

		for (string::iterator it = str.begin(); it != str.end(); it++)
		{
			out << (*it);
		}  */

		return out;
	}

	istream& operator>>(istream& in, string& str)
	{
		str.clear();		//��֮ǰ�Ŀռ�����һ��
		while (1)
		{
			char ch;
			ch = in.get();	//��ȡһ���ַ�
			if (ch == ' ' || ch == '\n')
			{
				break;
			}
			else
			{
				str += ch;
			}
		}
		return in;
	}

	istream& getline(istream& in, string& str)
	{
		str.clear();
		char ch;
		ch = in.get();
		while (ch != '\n')
		{
			str += ch;
			ch = in.get();
		}
		return in;
	}
}
