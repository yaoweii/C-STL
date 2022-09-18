#pragma once 
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
using namespace std;

//string的模拟实现
namespace yw			//创建一个自己的命名空间防止与c++的重名
{
	class string
	{
	private:
		size_t _capacity;		//能存储有效字符的个数，不包括字符串结尾\0
		size_t _size;			//有效字符个数
		char* _str;
	public:
		//有参构造
		//string(const char* = "\0")		//错误示范
		//string(const char* = nullptr)		//错误示范
		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];		//多开辟一个保留/0
			strcpy(_str, str);
		}

		/*拷贝构造
		string(const string& str)
		{
			_size = str._size;
			_capacity = str._capacity;
			_str = new char[str._capacity + 1];
			strcpy(_str, str._str);
		}
		//赋值重载
		string& operator=(const string& str)
		{
			if (this != &str)	//避免自己给自己赋值，导致原地址发生变化
			{
				_size = str._size;
				_capacity = str._capacity;
				char* tmp = new char[str._capacity + 1];	//深拷贝
				strcpy(tmp, str._str);		//调用string.h的库函数(复习c语言！)
				delete[] _str;		//删除原来的空间
				_str = tmp;
			}
			return *this;
		}*/

		//上面的是原来拷贝构造和赋值运算符重载的写法，现在写法如下(很妙)：

		void swap(string& str)		//其实这就是string里面的swap函数接口
		{
			std::swap(_str, str._str);		//使用std里面的swap库函数
			std::swap(_size, str._size);
			std::swap(_capacity, str._capacity);
		}

		string(const string& str) :_str(nullptr), _size(0), _capacity(0)
		{
			string tmp(str._str);	//以被拷贝对象的字符串，调用有参构造创建一个新的临时对象
			swap(tmp);
		}

		string& operator=(string str)	//因为传的值，所以会调用拷贝构造创建一个形参对象
		{
			swap(str);		//直接将形参和原对象交换
			return *this;	//函数运行完后，形参会销毁，但现在形参指向的是原对象的地址
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

		//clear():将原字符串清空，让其成为空串(空字符)
		void clear()
		{
			_size = 0;
			_str[0] = '\0';		//伪删除
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
			return *(_str + pos);		//str[pos]也可以
		}

		//c_str():返回c格式字符串
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
				delete[] _str;		//释放原空间
				_str = tmp;
				_capacity = n;
			}
			//已经大于或者等于n就不做处理
		}

		//resize()
		void resize(size_t n, const char& ch = char())
		{
			if (n <= _size)
			{
				_str[n] = '\0';		//如果n <= _size，那么只需要将n处的字符改成\0，标志字符串的结尾
			}
			else
			{
				if (n > _capacity)		//需要先扩容
				{
					reserve(n);
				}
				memset(_str + _size, ch, n - _size - 1);		//string.h里面的函数(复习c语言!)
				_str[n] = '\0';		//这里是字符串结尾的\0
			}
			_size = n;
		}

		//append():字符串追加
		void append(const char* str)
		{
			//先判断是否需要扩容
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
			assert(pos <= _size);		//因为insert是在pos之前插入，所以这里可以有等于
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
			//(_str + pos + strlen(str)表示这里原字符串末尾的\0也考虑进去了)
			strncpy(_str + pos, str, strlen(str));
			//复习string.h和stdlib.h库里面的函数

			_size = _size + strlen(str);
			return *this;
		}
	private:
		static const size_t npos;		//类外初始化
		//static const size_t npos = -1;		//也可以
	public:
		//erase():删除从pos位置开始(包括pos位置)后的n个字符串，如果n大于pos后面的字符个数，那么默认删除后面的所有字符，如果不传参数默认就是clear()
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
				//也可以strcpy(_str + pos, _str + pos + n);
				_size -= n;
			}
			return *this;
		}
		//npos:可以理解为size_t的最大值，关于其一些知识：https://mbd.baidu.com/ma/s/fl2sA3T8

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
			const char* ptr = strstr(_str + pos, str);		//string.h的库函数
			if (ptr == nullptr)
			{
				return npos;		//-1
			}
			else return ptr - _str;		//好秀！
		}

		//迭代器(string的迭代器就是一个char*指针重命名，必须要用迭代器的begin()和end()访问)
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

		//运算符重载
		friend bool operator==(string& str1, string& str2);
		friend bool operator<(string& str1, string& str2);
		friend bool operator<=(string& str1, string& str2);
		friend bool operator>(string& str1, string& str2);
		friend bool operator>=(string& str1, string& str2);
		friend ostream& operator<<(ostream& out, string& str);
		friend istream& operator>>(istream& in, string& str);
		friend istream& getline(istream& in, string& str);
	};

	//string类外：
	const size_t string::npos = -1;		//npos定义为-1

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

	//cout、cin和getline
	ostream& operator<<(ostream& out, string& str)
	{
		for (auto e : str)		//使用begin()和end()范围循环
		{
			out << e;
		}
		//这里不能用cout << str.c_str();

		/*也可以如下：
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
		str.clear();		//把之前的空间清理一下
		while (1)
		{
			char ch;
			ch = in.get();	//获取一个字符
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
