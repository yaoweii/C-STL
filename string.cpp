#include <iostream>
#include <string>
#include <cassert>
using namespace std;
/*string�ࣺ
1. string�Ǳ�ʾ�ַ������ַ�����
2. ����Ľӿ��볣�������Ľӿڻ�����ͬ���������һЩר����������string�ĳ������
3. string�ڵײ�ʵ���ǣ�basic_stringģ����ı�����typedef basic_string<char,char_traits,allocator> string;
4. ���ܲ������ֽڻ��߱䳤�ַ������� */

//string�ೣ�ýӿ�
void test()
{
	//���캯��
	//string()���޲ι��죬����һ�����ַ���
	string str1;

	//string(const char* s)���вι���
	const char* str = "hello world";
	string str2("abcd");

	//string(int n, char c)���вι���
	string str3(5, 'c');
	cout << str3 << endl;		//ccccc

	//string(const string& str, size_t pos = 0, size_t n = npos)����������
	string str4(str3);


	//size():�����ַ�������Ч�ַ�����
	string s = "hello\nworld!";
	cout << s.size() << endl;		//12���Ὣ\n���ȥ��string�������ʱ��������Զ�����һ��\0,

	//capacity():���ؿռ��ܴ�С
	cout << s.capacity();			//15

	//empty():����ַ����Ƿ�Ϊ�մ����Ƿ���true
	string s1;
	cout << s1.empty();		//1

	//clear():�����Ч�ַ�����ʹ���ɿմ�
	s.clear();
	cout << s.empty();		//1
	cout << s.capacity();	//capacity�Ŀռ䲻��仯

	//reserve(size_t n):����
	s1.reserve(20);			//����Ϊs1�洢��Ч�ַ�Ԥ��20���ռ�
	cout << s1.capacity();	//31
	
	//�鿴vs��reverse��capacity�����ݹ���
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

	//resize(size_t n, char ch = char()):����Ч�ַ������ĳ�n�������������ch���
	string s2 = "temp";
	cout << s2.size();		//4
	s2.resize(6);
	cout << s2.size();		//6

	//���resizeС��ԭ��Ч�ַ����ȣ���ô���ȡǰn���ַ�
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
	//��posλ�ÿ�ʼ�����Ӵ�str������ҵ��˾ͷ��ص�һ�γ����Ӵ�ʱ�����������Ӵ����ַ����±�
	//���û���ҵ��Ӵ�������-1
	str1 = "abcdef";
	size_t pos = str1.find("cd");
	cout << pos << endl;		//2

	//2. int find(const char* str, int pos = 0) const
	//3. int rfind(const string& str, int pos = npos) const
	pos = str1.rfind("cd");
	cout << str1 << endl;		//2
	//find��rfind������:find�Ǵ������Ҳ��ң�rfind�Ǵ����������(reverse find)


	//�滻
	//string& replace(int pos, int n, const char* str)
	str1.replace(1, 3, "1111");		//���ַ���1��λ���������ַ����滻��"1111"
	cout << str1 << endl;		//a1111ef


	//string�ַ����Ƚ�
	//int compare(const char* str)const
	//int compare(const string& str)const
	int ret = str1.compare(str2);		//���str1>str2������1�����str1<str2������-1��������ڷ���0


	//operator[size_t pos]():����posλ�õ��ַ�(�ɶ���д)
	str1 = "abcdef";
	for (int i = 0; i < str1.size(); i++)
	{
		cout << str1[i] << " ";
	}


	//at():���ʵ����ַ�(�ɶ���д)
	for (int i = 0; i < str1.size(); ++i)
	{
		cout << str1.at(i) << " ";
	}

	//begin():��ȡ��һ���ַ��ĵ�����
	s = "hello";
	string::iterator it = s.begin();
	cout << *it << endl;			//h
	
	//end():��ȡ���һ���ַ�����һ��λ�õĵ�����
	string::iterator end_it = s.end();
	cout << *(--end_it) << endl;	//o

	//cbegin()��cend():��begin/end�ĺ������أ����ص���const_iterator

	//rbegin():reverse_begin����ȡ��һ���ַ��ķ��������reverse_iterator
	//rend():��ȡ��һ���ַ���ǰһ��λ�õĵ�����
	for (string::reverse_iterator r_it = s.rbegin(); r_it != s.rend(); r_it--)
	{
		cout << *r_it;
	}
	
	//push_back():�ں���׷��һ���ַ�
	s1 = "hello";
	s1.push_back('!');
	cout << s1;			//hello!

	//pop_back():ɾ���ַ��������һ���ַ�
	s1.pop_back();
	cout << s1;			//hello


	//append():���ַ�������׷��һ���ַ�
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
	//��str�ַ���posλ�ÿ�ʼ׷��n���ַ���Ps:�ַ�����һ��λ�õ��±�pos��0
	str2 = "LOL DNF";
	str1 = "I LOVE ";
	str1.append(str2, 0, 3);
	cout << str1 << endl;		//I LOVE LOL
	str1.append(str2, 4, 3);
	cout << str1 << endl;		//I LOVE DNF


	//stringû��pop_front()��push_front()�����ǿ�����insert()��erase()����
	//insert():���±�Ϊpos֮ǰ����
	//string& insert(int pos, const char* str)
	//string& insert(int pos, const string& str)
	str1 = "abcdef";
	str1.insert(1, "1111");
	cout << str1 << endl;		//a1111bcdef
	//string& insert(int pos, int n, char c)
	str1 = "abcdef";
	str1.insert(1, 4, '1');
	cout << str1 << endl;		//a1111bcdef


	//string& erase(size_t pos, size_t len = npos):���±�Ϊpos��ʼ��ɾ�������len���ַ�
	s1 = "hello world";
	s1.erase(0, 6);
	cout << s1;				//world

	//const char* c_str():����c��ʽ���ַ���������\0����ֹ
	s1 = "input";
	s1.resize();
	cout << s1.c_str();		//input

	//ע�⣺
	s1.resize(20);
	s1 += " 123";
	cout << s1;		//input 123
	cout << s1.c_str();		//input
	//���������˵����cout<<s1�ǰ���size������ӡ������\0����ӡ��ʾ����cout<<s1.c_str()����\0����ֹ��

	//������������ǲ�����ʽȥ��\0����Ȼ�������������\0����ֹ��
	s1 = "hello\0world";
	cout << s1;				//hello
	cout << s1.c_str();		//hello

	s1 += ".cpp";
	cout << s1;				//hello.cpp
	cout << s1.c_str();		//hello.cpp
	//���Ƿ��֣����߶��Ǵ�\0��ʼ���룬������Ϊ�ڱ����ʱ������\0����ֹ�ˣ�����s1�洢���ַ�������hello


	//substr();��posλ�ÿ�ʼ����ȡn���ַ������䷵��
	//string substr(size_t pos = 0, int n = npos) const
	str1 = "abcdef";
	string substr = str1.substr(1, 3);
	cout << substr << endl;		//bcd

	string email = "zhangsan@qq.com";
	//���������л�ȡ�û���Ϣ
	size_t pos = email.find('@');
	string information = email.substr(0, pos);
	cout << information << endl;		//zhangsan

	//getline():��ȡһ���ַ������������о���ֹ�������ո���ֹ
	getline(cin, s1);
	cout << s1;

	//cin��scanf:�����ո���о�ֹͣ��ȡ
	s1.clear();
	cin >> s1;		//����hello cpp
	cout << s1;		//hello
}


//ģ��ʵ��string��Ĳ���
#define _CRT_SECURE_NO_WARNINGS			//��������vs�����������⣬ʹ��strcpy����ʱ�ᱨ������ȫ�����Լ��������
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

	//���Ե�����
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
