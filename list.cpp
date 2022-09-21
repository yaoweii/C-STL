#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <cassert>
using namespace std;
/*list容器：
1. list是可以在常数范围内在任意位置进行插入和删除的序列式容器，并且该容器可以前后双向迭代
2. list的底层是双向链表结构，双向链表中每个元素存储在互不相关的独立节点中，在节点中通过指针指向其前一个元素和后一个元素
3. list与forward_list非常相似：最主要的不同在于forward_list是单链表，只能朝前迭代，已让其更简单高效
4. 与其他的序列式容器相比(array，vector，deque)，list通常在任意位置进行插入、移除元素的执行效率更好
5. 与其他序列式容器相比，list和forward_list最大的缺陷是不支持任意位置的随机访问
	比如：要访问list的第6个元素，必须从已知的位置(比如头部或者尾部)迭代到该位置，在这段位置上迭代需要线性的时间开销
	list还需要一些额外的空间，以保存每个节点的相关联信息(对于存储类型较小元素的大list来说这可能是一个重要的因素
6. list插入和删除其他元素都不会造成该迭代器失效（即其地址不变，因为他是通过next和prev指针来访问），这里和vector不同
7. 由于list的储存空间不是连续的，所以迭代器只能前后移动(重载++，--)来访问，不能*(pos + n)访问  */

template<class T>
struct down
{
	bool operator()(T val1, T val2)
	{
		return val1 > val2;
	}
};

//list容器的常用接口介绍
void test()
{
	//构造函数
	//list():构造空链表
	list<int> st1;
	cout << st1.size();		//0

	//lsit(size_t n, const T& val = T())
	list<int> st2(10, 100);

	//lsit(Inputiterator first, Inputiterator last)
	list<int> st3(st2.begin(), st2.end());

	//list(const list& st)
	list<int> st4(st1);

	//其他
	list<int> st5 = { 9,8,7,6,5,4 };
	
	//迭代器
	list<int>::iterator it = st1.begin();		//返回第一个元素的迭代器
	list<int>::iterator it = st1.end();			//返回最后一个元素的下一个位置的迭代器(实际上是哨兵位的迭代器)
	list<int>::const_iterator c_it = st1.cbegin();
	list<int>::reverse_iterator r_it = st1.rbegin();	//返回最后一个元素的迭代器
	list<int>::reverse_iterator r_it = st1.rend();		//返回第一个元素的前一个位置的迭代器(实际上就是哨兵位)
	list<int>::const_reverse_iterator c_r_it = st1.crbegin();
	//注意：如果是const对象调用rbegin，那么返回的是const类型的反向迭代器(其他容器也一样)

	//注意：对反向迭代器执行++操作，迭代器向前移
	list<int> test = { 1,2,3,4,5 };
	for (list<int>::reverse_iterator r_it = test.rbegin(); r_it != test.rend();)
	{
		cout << *r_it << ' ';
		r_it++;
	}			//5 4 3 2 1

	//empty():判断是否为空
	cout << list<int>().empty();		//1

	//size():返回list中有效数据个数
	cout << st1.size();

	//list中没有capacity()接口，因为插入一个数据就开辟一个空间

	//front():返回list中第一个节点的值，如果没有就抛出异常
	cout << st1.front();

	//back():返回容器中最后一个节点的值，如果没有抛出异常
	cout << st1.back();

	//push_back():尾插
	st1.push_back(2);

	//pop_back():尾删，如果只有头结点了则抛出异常
	st1.pop_back();

	//push_front():头插
	st1.push_front(2);

	//pop_front():头删，如果只剩头结点则抛出异常
	st1.pop_front();

	//iterator insert(iterator pos, const T& val):在迭代器pos之前插入val，返回插入位置的迭代器
	st1.insert(st1.begin(), 2);

	//iterator erase(iterator pos):删除pos位置的数据
	//iterator erase(iterator first, iterator last):删除迭代器区间的数据，左闭右开[first,last)，其他容器也是一样
	list<int>::iterator it = find(st1.begin(), st1.end(), 2);		//这里find用法和vector中一样，都是算法库里面的
	st1.erase(it);
	st1.erase(st1.begin(), st1.end());

	//swap():交换两个list容器，实际上就是交换头结点的指针
	st1.swap(st2);

	//clear():清除list中的所有元素
	st1.clear();
	cout << st1.empty();	//1

	//operator=
	st1 = st2;

	//remove(const T& val):清除list中所有的val值
	st1 = { 1,2,2,2,3 };
	st1.remove(2);
	for (auto e : st1)
	{
		cout << e << ' ';
	}		//1 3

	//splice():把一个对象里面指定位置的迭代器转移到另一个对象上面
	//splice(iterator pos, list& st):把st对象里面的所有数据转移到调用该函数的对象中pos迭代器的前面
	st1 = { 1,3,5,7 };
	st2 = { 2,4,6,8 };
	list<int>::iterator it = find(st1.begin(), st1.end(), 2);
	st1.splice(it, st2);
	for (auto e : st1)
	{
		cout << e << " ";
	}						//1 2 4 6 8 3 5 7
	//此时st2已结变成了空链表

	//splice(iterator pos1, list& st, iterator pos2):把st对象中pos2位置的迭代器移到调用该函数的对象中pos1位置迭代器的前面
	st3 = { 10,20,30,40 };
	st4 = { 1,2,3,4 };
	list<int>::iterator it3 = find(st3.begin(), st3.end(), 20);
	list<int>::iterator it4 = find(st4.begin(), st4.end(), 2);
	st3.splice(it3, st4, it4);
	for (auto e : st3)
	{
		cout << e << " ";
	}						//10 2 30 40 50
	for (auto e : st4)
	{
		cout << e << ' ';
	}						//1 3 4

	//sort():对链表排序，默认升序(不推荐使用，效率低，甚至不如将数据拷贝到vector排序后再拷贝到list效率高)
	st1 = { 1,5,4,9,6,3 };
	st1.sort();
	for (auto e : st1)
	{
		cout << e << " ";
	}						//1 3 4 5 6 9

	//降序写法(使用仿函数)
	down<int> down;
	st1.sort(down);

	//assign(iterator begin, iterator end):将[begin,end)区间的值赋给本身
	st2.assign(st1.begin(), st1.end());

	//assign(size_t n, T& val)
	st2.assign(10, 100);

	//resize(size_t n, T& val = T())
	st1.resize(100);
	//list容器是插入一个元素才会创建内存空间，所以resize必须初始化(一般list容器不会使用resize)

	//reverse():反转链表
	st1.reverse();
}


//list迭代器失效
void test()
{
	//list由于是双向链表结构，所以插入元素时不会导致list迭代器失效
	//因为list空间不连续，不存在挪动数据的情况
	//所以只有删除时才会失效，并且失效的只是指向被删除节点的迭代器

	list<int> st = { 1,2,3,4,5,6 };
	for (list<int>::iterator it = st.begin(); it != st.end();)
	{
		st.erase(it);
		//it++;		//erase后原it迭代器就失效了，不能使用迭代器++了
		//因为这里++是重载的，我们可以将it理解为一个对象，++并不是简单的地址向前移动

		//正确做法
		//1.重新给it赋值
		it = st.begin();
		//2.
		st.erase(it++);		//这里要参考list模拟实现中的后置++实现和erase实现
	}
}


//算法排序
//sort(st1.begin(), st1.end());		//error
//sort排序时快速排序，必须支持随机存取的数据结构才能实现，而list空间不是连续的，不支持随机访问

//排序案例
//创建一个类，先按年龄升序，再按名字降序
class Person {
public:
	int age;
	string name;
	int high;
	Person(string name,int age,int high):name(name),age(age),high(high){}
};
//指定排序规则（回调函数:就是作为其他函数参数的函数），这里也可以写成仿函数
bool compare(Person& p1, Person& p2)
{
	//按照年龄升序
	if (p1.age == p2.age)
	{
		//如果年龄相同，按照名字降序
		return p1.name > p1.name;
	}
	return p1.age < p2.age;
}
int main()
{
	list<Person> L1(5);
	//创建数据
	Person p1("刘备", 50, 176);
	Person p2("关羽", 40, 180);
	Person p3("张飞", 35, 180);
	Person p4("马超", 40, 190);
	Person p5("赵云", 35, 188);
	Person p6("诸葛亮", 55, 170);
	//插入数据
	L1.push_back(p1);
	L1.push_back(p2);
	L1.push_back(p3);
	L1.push_back(p4);
	L1.push_back(p5);
	L1.push_back(p6);

	L1.sort();		//error，编译器不知道怎么排序
	//指定排序规则
	L1.sort(compare);
	return 0;
}


//list模拟实现的测试
#include "list.h"
using namespace std;
int main()
{
	yw::list<string> st1;
	st1.push_back("张三");
	st1.push_front("李四");
	st1.insert(st1.begin(), "王五");

	for (auto e : st1)
	{
		cout << e << " ";
	}
	cout << endl;

	yw::list<string> st2(st1);
	st1.pop_back();
	st1.pop_front();
	st1.erase(--(st1.end()));
	cout << st1.empty() << endl;

	st1 = st2;
	cout << st2.empty() << endl;

	st2.clear();
	cout << st2.empty() << endl;
	return 0;
}

//关于迭代器中->的使用
class date {
public:
	int month;
	int day;
	int year;
};
void test()
{
	yw::list<date> st;
	date d1;
	for (int i = 0; i < 5; i++)
	{
		st.push_back(d1);
	}
	yw::list<date>::iterator it = st.begin();

	(*it).day;
	it->day;				//虽然->返回的是数据的指针，但也可以直接访问到数据里的成员变量
	it.operator->()->day;	//这样子才符合重载函数实现的逻辑(即返回的是数据的指针)
	st.clear();
}