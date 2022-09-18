#include <iostream>
#include <string>
#include <cassert>
using namespace std;
/*string类：
1. string是表示字符串的字符串类
2. 该类的接口与常规容器的接口基本相同，再添加了一些专门用来操作string的常规操作
3. string在底层实际是：basic_string模板类的别名，typedef basic_string<char,char_traits,allocator> string;
4. 不能操作多字节或者变长字符的序列 */

//string类常用接口
void test()
{
	//构造函数
	//string()：无参构造，创建一个空字符串
	string str1;

	//string(const char* s)：有参构造
	const char* str = "hello world";
	string str2("abcd");

	//string(int n, char c)：有参构造
	string str3(5, 'c');
	cout << str3 << endl;		//ccccc

	//string(const string& str, size_t pos = 0, size_t n = npos)：拷贝构造
	string str4(str3);


	//size():返回字符串中有效字符长度
	string s = "hello\nworld!";
	cout << s.size() << endl;		//12，会将\n算进去，string定义对象时会在最后自动补上一个\0,

	//capacity():返回空间总大小
	cout << s.capacity();			//15

	//empty():检测字符串是否为空串，是返回true
	string s1;
	cout << s1.empty();		//1

	//clear():清除有效字符串，使其变成空串
	s.clear();
	cout << s.empty();		//1
	cout << s.capacity();	//capacity的空间不会变化

	//reserve(size_t n):扩容
	s1.reserve(20);			//至少为s1存储有效字符预留20个空间
	cout << s1.capacity();	//31
	
	//查看vs中reverse是capacity的扩容规则：
	string st;
	size_t sz = st.size();
	for (size_t i = 0; i < 500; i++)
	{
		st.push_back('c');
		if (sz != st.capacity())
		{
			cout << "capacity is change to" << st.capacity() << endl;
			sz = st.capacity();
		}
	}

	//resize(size_t n, char ch = char()):将有效字符个数改成n个，多出来的用ch填充
	string s2 = "temp";
	cout << s2.size();		//4
	s2.resize(6);
	cout << s2.size();		//6

	//如果resize小于原有效字符长度，那么会截取前n个字符
	string s3 = "my name is xxx";
	s3.resize(7);
	cout << s3;			//my name
	
	//string& operator=(const char* str)
	//string& operator=(const string& str)
	//string& operator=(const char& c)
	str1 = "hello cpp";
	str2 = str1;
	str1 = 'c';

	//string& operator+=(const char* str)
	//string& operator+=(const char& c)
	//string& operator+=(const string& str)
	str1 = "name";
	str1 += "is me";
	cout << str1 << endl;		//name is me

	str2 = " haha";
	str1 += str2;
	cout << str1 << endl;		//name is me haha


	//1. int find(const string& str, int pos = 0) const
	//从pos位置开始查找子串str，如果找到了就返回第一次出现子串时，主串的中子串首字符的下标
	//如果没有找到子串，返回-1
	str1 = "abcdef";
	size_t pos = str1.find("cd");
	cout << pos << endl;		//2

	//2. int find(const char* str, int pos = 0) const
	//3. int rfind(const string& str, int pos = npos) const
	pos = str1.rfind("cd");
	cout << str1 << endl;		//2
	//find和rfind的区别:find是从左往右查找，rfind是从右往左查找(reverse find)


	//替换
	//string& replace(int pos, int n, const char* str)
	str1.replace(1, 3, "1111");		//从字符串1号位置起，三个字符串替换成"1111"
	cout << str1 << endl;		//a1111ef


	//string字符串比较
	//int compare(const char* str)const
	//int compare(const string& str)const
	int ret = str1.compare(str2);		//如果str1>str2，返回1，如果str1<str2，返回-1，如果等于返回0


	//operator[size_t pos]():返回pos位置的字符(可读可写)
	str1 = "abcdef";
	for (int i = 0; i < str1.size(); i++)
	{
		cout << str1[i] << " ";
	}


	//at():访问单个字符(可读可写)
	for (int i = 0; i < str1.size(); ++i)
	{
		cout << str1.at(i) << " ";
	}

	//begin():获取第一个字符的迭代器
	s = "hello";
	string::iterator it = s.begin();
	cout << *it << endl;			//h
	
	//end():获取最后一个字符的下一个位置的迭代器
	string::iterator end_it = s.end();
	cout << *(--end_it) << endl;	//o

	//cbegin()，cend():是begin/end的函数重载，返回的是const_iterator

	//rbegin():reverse_begin，获取最一个字符的反向迭代器reverse_iterator
	//rend():获取第一个字符的前一个位置的迭代器
	for (string::reverse_iterator r_it = s.rbegin(); r_it != s.rend(); r_it--)
	{
		cout << *r_it;
	}
	
	//push_back():在后面追加一个字符
	s1 = "hello";
	s1.push_back('!');
	cout << s1;			//hello!

	//pop_back():删除字符串中最后一个字符
	s1.pop_back();
	cout << s1;			//hello


	//append():在字符串后面追加一个字符
	//string& append(const char* str)
	str1 = "name is me haha";
	str1.append(" please");
	cout << str1 << endl;		//name is me haha please
	//string& append(const string& str)
	str2 = "ggboy";
	str1.append(str2);

	//string& append(const char* str, int n)
	str1.append(" loveeee", 5);
	cout << str1 << endl;		//name is mec haha please love

	//string& appen(const string& str, int pos, int n)
	//从str字符串pos位置开始追加n个字符，Ps:字符串第一个位置的下标pos是0
	str2 = "LOL DNF";
	str1 = "I LOVE ";
	str1.append(str2, 0, 3);
	cout << str1 << endl;		//I LOVE LOL
	str1.append(str2, 4, 3);
	cout << str1 << endl;		//I LOVE DNF


	//string没有pop_front()和push_front()，但是可以用insert()和erase()代替
	//insert():在下标为pos之前插入
	//string& insert(int pos, const char* str)
	//string& insert(int pos, const string& str)
	str1 = "abcdef";
	str1.insert(1, "1111");
	cout << str1 << endl;		//a1111bcdef
	//string& insert(int pos, int n, char c)
	str1 = "abcdef";
	str1.insert(1, 4, '1');
	cout << str1 << endl;		//a1111bcdef


	//string& erase(size_t pos, size_t len = npos):从下标为pos开始，删除后面的len个字符
	s1 = "hello world";
	s1.erase(0, 6);
	cout << s1;				//world

	//const char* c_str():返回c格式的字符串，遇到\0就终止
	s1 = "input";
	s1.resize();
	cout << s1.c_str();		//input

	//注意：
	s1.resize(20);
	s1 += " 123";
	cout << s1;		//input 123
	cout << s1.c_str();		//input
	//上面的例子说明：cout<<s1是按照size个数打印的遇到\0不打印显示，而cout<<s1.c_str()遇到\0就终止了

	//特殊情况：我们不能显式去传\0，不然两种情况都遇到\0就终止了
	s1 = "hello\0world";
	cout << s1;				//hello
	cout << s1.c_str();		//hello

	s1 += ".cpp";
	cout << s1;				//hello.cpp
	cout << s1.c_str();		//hello.cpp
	//我们发现，两者都是从\0开始插入，这是因为在编译的时候遇到\0就终止了，所以s1存储的字符串就是hello


	//substr();从pos位置开始，截取n个字符，将其返回
	//string substr(size_t pos = 0, int n = npos) const
	str1 = "abcdef";
	string substr = str1.substr(1, 3);
	cout << substr << endl;		//bcd

	string email = "zhangsan@qq.com";
	//从邮箱名中获取用户信息
	size_t pos = email.find('@');
	string information = email.substr(0, pos);
	cout << information << endl;		//zhangsan

	//getline():获取一行字符串，遇到换行就终止，遇到空格不终止
	getline(cin, s1);
	cout << s1;

	//cin、scanf:遇到空格或换行就停止读取
	s1.clear();
	cin >> s1;		//输入hello cpp
	cout << s1;		//hello
}


//模拟实现string类的测试
#define _CRT_SECURE_NO_WARNINGS			//这里由于vs编译器的问题，使用strcpy函数时会报出不安全，所以加上这个宏
#include <string>
#include <iostream>
#include "string.h"
using namespace std;
int main()
{
	yw::string str1;
	cin >> str1;
	cout << str1 << endl;;

	str1.push_back('a');
	cout << str1 << endl;

	str1.insert(0, 'a');
	cout << str1 << endl;

	yw::string str2("this is string");
	cout << str2;

	yw::string str3(str2);
	cout << str3 << endl;

	cout << str3.c_str() << endl;

	//测试迭代器
	for (auto e : str3)
	{
		cout << e;
	}
	cout << endl;

	cout << "str3.capacity = " << str3.capacity() << endl << "str3.size = " << str3.size() << endl;

	str3.append("\nthis is a test for append()");
	cout << str3 << endl;

	str2.erase();
	cout << str2.empty() << endl;

	cout << str3.find("is") << endl;		//2

	str3.insert(0, "test for insert\n");
	cout << str3 << endl;

	str3.swap(str2);
	cout << str2;

	cout << str2[3] << endl;

	str2.clear();
	cout << str2.empty() << endl;
	return 0;
}
