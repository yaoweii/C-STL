#include <iostream>
#include <vector>			//使用容器时都必须要包含头文件
#include <algorithm>		//标准算法的头文件
#include <cassert>
#include <cstdlib>
using namespace std;
/*vector
1. vector是表示可变大小数组的序列容器
2. 就像数组一样，vector也采用的连续存储空间来存储元素。也就是意味着可以采用下标对vector的元素进行访问，和数组一样高效
但是又不像数组，它的大小是可以动态改变的，而且它的大小会被容器自动处理
3. 本质讲，vector使用动态分配数组来存储它的元素。当新元素插入时候，这个数组需要被重新分配大小为了增加存储空间
其做法是，分配一个新的数组，然后将全部元素移到这个数组。就时间而言，这是一个相对代价高的任务，
因为每当一个新的元素加入到容器的时候，vector并不会每次都重新分配大小。
4. vector分配空间策略：vector会分配一些额外的空间以适应可能的增长，因为存储空间比实际需要的存储空间更大
不同的库采用不同的策略权衡空间的使用和重新分配。但是无论如何，重新分配都应该是对数增长的间隔大小，
以至于在末尾插入一个元素的时候是在常数时间的复杂度完成的。
5. 因此，vector占用了更多的存储空间，为了获得管理存储空间的能力，并且以一种有效的方式动态增长
6. 与其它动态序列容器相比(deques, lists and forward_lists)， vector在访问元素的时候更加高效，
在末尾添加和删除元素相对高效。对于其它不在末尾的删除和插入操作，效率更低。比起list和forward_lists统一的迭代器和引用更好 */


//vector的常用函数接口
void test()
{
	//构造函数
	//vector()
	vector<int> vtr1;
	cout << vtr1.capacity() << vtr1.size();		//结果都是0，说明里面没有任何数据

	//vector(size_t n, const T& val = T())
	vector<int> vtr2(10);
	cout << vtr2.size();		//10，里面初始化数据为val

	vector<vector<int>> arr(10, vector<int>(10, 5));	//相当于二维数组

	//vector(const vector& vtr)
	vector<int> vtr3 = vtr1;

	//其他初始化
	vector<int> arr1 = { 1,2,3,4 };
	

	//迭代器
	vector<int>::iterator it = vtr1.begin();			//普通迭代器
	vector<int>::const_iterator c_it = vtr1.cbegin();	//常量迭代器，不可修改，只可以访问
	vector<int>::reverse_iterator r_it = vtr1.rbegin();	//反向迭代器，rbegin()返回容器最后一个位置数据的指针
	//rend()返回第一个的前一个位置指针

	//size()、capacity
	vtr1.push_back(1);
	cout << vtr1.size() << endl << vtr1.capacity();	

	//empty():判断是否为空，是就返回true
	vtr1.empty();		//false

	//resize(size_t n, const T& val = T()):改变容器中的数据个数(size)，如果size<n，则用val初始化

	//reserve():改变容器的capacity
	vtr1.reserve(20);
	cout << vtr1.capacity();		//20
	//注意：reserve()扩容是扩容到指定大小，而不是至少是指定大小，revers可以缓解vector增容的代价缺陷问题

	//探讨VS中capacity的增容规则
	vector<int> test;
	size_t sz = test.capacity();
	for (int i = 0; i < 500; i++)
	{
		test.push_back(4);
		if (test.capacity() != sz)
		{
			cout << "capacity change to:" << test.capacity() << endl;
			sz = test.capacity();
		}
	}

	//push_back():尾插
	vtr1.push_back(10);
	vtr2.push_back(20);

	//pop_back():尾删
	vtr1.pop_back();

	//find():算法库algorithm.h提供的(string里面的find是string自己的)，不是vector成员的接口，使用时传迭代器区间
	vector<int>::iterator f_it = find(vtr1.begin(), vtr1.end(), 2);

	//insert():在指定位置(迭代器)前插入数据val，vector没有头插头删(效率太低)，可以使用insert代替(少用)
	vtr1.insert(vtr1.begin(), 1);
	//注意第一个参数是迭代器，并且插入的位置是指定位置的前面，使插入的元素的位置变成指定位置

	//assign():删除原空间的数据，然后赋值
	vtr2.assign(vtr1.begin(), vtr1.end());
	//assign(int n, T elem)
	vtr2.assign(10, 100);

	//erase()
	vtr1.erase(vtr1.begin());		//删除begin()位置的数据
	vtr1.erase(vtr1.begin(), vtr1.end());			//删除迭代器begin()和end()区间的数据

	//swap():交换两个容器的数据(底层原理是交换指针)
	vtr1.swap(vtr2);		//vtr1和vtr2容器互换

	//swap的实际应用：收缩空间
	vector<int> v2;
	for (int i = 0; i < 100000; i++)
	{
		v2.push_back(i);
	}
	v2.resize(3);		//此时size变成3，但是容量却大于100000
	vector<int>(v2).swap(v2);
	//相当于拷贝构造创建了一个匿名对象，然后再用匿名对象和v2容器互换，此时capacity会变小(细看vector的模拟实现)

	//at():访问vector中的元素(返回的是引用)
	cout << vtr1.at(1);

	//front():获取容器第一个元素
	int front = vtr1.front();

	//back():获取容器最后一个元素(返回的是引用)
	int back = vtr1.back();

	//clear():删除容器中的所有元素
	v2.clear();
	
	//operator[]:访问容器中的元素
	int a = vtr1[1];


	//vector容器的遍历
	//第一种
	for (vector<int>::iterator it = vtr1.begin(); it != vtr1.end(); it++)
	{
		cout << *it << " ";
	}
	
	//第二种：范围for循环
	for (auto i : vtr1)
	{
		cout << i;
	}


	//二维数组遍历
	for (vector<vector<int>>::iterator it = arr.begin(); arr.end() != it; ++it)
	{
		for (vector<int>::iterator vit = (*it).begin(); vit != (*it).end(); ++vit)
		//vector<int>::iterator，这里不能使用(*it)::iterator，因为vector<int>是指定类型，而(*it)不是类型(细看vector模拟实现)
		{
			cout << *vit << " ";
		}
		cout << endl;
	}
}


//vector迭代器失效问题
void test1()
{
	/*迭代器的主要作用就是让算法能够不用关心底层数据结构，其底层实际就是一个指针，或者是对指针进行了封装
	比如：vector的迭代器就是原生态指针T*。因此迭代器失效，实际就是迭代器底层对应指针所指向的空间被销毁了
	而使用一块已经被释放的空间，造成的后果是程序崩溃(即如果继续使用已经失效的迭代器，程序可能会崩溃)*/

	//1.因为扩容导致迭代器失效
	/*使用resize()、reserve()、insert()、push_back()、assign()等操作时，会引起容器空间的改变，当需要扩容时
	如果扩容方式是异地扩容(参考c语言中的calloc函数),那么原来的迭代器就指向旧空间(异地扩容后就销毁了)*/
	//举例
	vector<int> vtr;
	for (int i = 0; i < 6; i++)
	{
		vtr.push_back(i);
	}
	vector<int>::iterator it = find(vtr.begin(), vtr.end(), 2);
	cout << "插入前，*it = " << *it << endl;		//2
	vtr.insert(it, 6);
	cout << "插入后，*it = " << *it << endl;		//程序崩溃
	//因为此时发生了异地扩容，原内存被释放，导致这里的it指针变成野指针，指向不再是容器了
	//注意：如果没有发生扩容，那么这里*it指向的值应该是insert的val值(细看vect才变成野指针的or模拟实现中的insert)
	//这里是insert之后it才变成野指针的

	/*提问：这里it是形参，所以不会改变it本身的值(insert函数内部发现需要异地扩容后会改变pos值)，如果我们传入引用是不是可以避免问题？
	答案：是的，但是会产生新的问题，所以我们不建议传引用，其insert本身底层实现也是如此	*/

	//解决方式：给it重新赋值即可
	it = vtr.insert(it, 6);			//此时it的值就是insert函数返回的pos值(新的地址)
	//具体可以参考vector的模拟实现


	//2.因为删除数据(erase)导致迭代器失效
	//iterator erase(iterator pos):删除pos位置的元素，返回要删除位置的迭代器的下一个迭代器
	vector<int> vtr1;
	for (int i = 0; i < 5; i++)
	{
		vtr1.push_back(i);
	}
	vector<int>::iterator it1 = find(vtr1.begin(), vtr1.end(), 3);
	vtr1.erase(it1);
	cout << *it1;		//程序崩溃
	/*如果我们每次erase后使用该迭代器我们使用VS编译程序直接崩溃了，但是使用其他编译器可能不会崩溃
	实际上上面erase后*it1的值为4 
	
	erase删除pos位置元素后，pos位置之后的元素会往前搬移，没有导致底层空间的改变，理论上讲迭代器不应该会失效，
	但是：如果pos刚好是最后一个元素，删完之后pos刚好是_finish的位置，而_finish位置是没有元素的，那么pos就失效了
	因此删除vector中任意位置上元素时，vs就认为该位置迭代器失效了 */
	
	//解决方法：使用前对该迭代器重新赋值
}


//关于vector两次push_back三次构造
class A
{
public:
	A()
	{
		cout << "构造函数";
	}
	~A()
	{
		cout << "析构函数";
	}
};

void test()
{
	A a;
	vector<A> vtr;
	vtr.push_back(a);
	vtr.push_back(a);
	//运行结果：一共打印四遍构造函数和析构函数
	/*原因：
	第一次：创建对象a
	第二次：push_back调用，调用拷贝构造函数拷贝对象a
	第三次：vector异地扩容，数据地址发生变化，所以第一个元素被转移，此时转移发生了一次构造函数
	第四次：第二次push_back
	
	提问:push_back不是串的引用吗，为什么还是会调用构造函数？
	因为push_back底层调用的是insert，而insert参数是值传递	*/

	vector<A> vtr1;
	vtr1.resize(2);
	vtr1.push_back(a);
	vtr1.push_back(a);		//此时就只有两次了
}


//模拟实现vector测试
#include <string>
#include <iostream>
#include "vector.h"
using namespace std;
int main()
{
	yw::vector<string> vtr1;
	vtr1.push_back("张三");
	vtr1.insert(vtr1.begin(), "李四");
	cout << "size = " << vtr1.size() << "capacity = " << vtr1.capacity() << endl;
	for (auto e : vtr1)
	{
		cout << e;
	}
	cout << endl;

	yw::vector<string> vtr2(vtr1);
	cout << vtr2[0] << endl;

	yw::vector<string> vtr3;
	vtr3.swap(vtr2);
	cout << vtr3.size() << "  " << vtr3[0] << endl;

	vtr2 = vtr3;
	cout << vtr2.capacity() << "  " << vtr2[1] << endl;

	vtr2.erase(vtr2.rbegin());
	for (yw::vector<string>::iterator it = vtr2.begin(); it != vtr2.end(); ++it)
	{
		cout << *it;
	}
	cout << endl;

	vtr2.resize(10);
	vtr2.reserve(20);
	cout << vtr2.size() << "  " << vtr2.capacity() << endl;
	return 0;
}


