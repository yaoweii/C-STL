#include <iostream>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

/*序列式容器和关联式容器
序列式容器：vector，list，deque等。底层为线性序列的数据结构，其中存放元素本身

关联式容器：存放的是pair<key,value>结构的键值对，根据应用场景的不桶，STL总共实现了两种不同结构的管理式容器：树型结构与哈希结构
树型结构的关联式容器主要有四种：map、set、multimap、multiset
这四种容器的共同点是：其底层实现使用平衡搜索树(红黑树)，容器中的元素是一个有序的序列

哈希结构的关联式容器有：unordered_set、unordered_map、unordered_multiset、unordered_multimap
这四种容器的共同点是：其底层实现使用哈希表，但是容器中的元素无序	*/


//set容器介绍

//set容器模板参数
/*template<class T, class Compare = less<T>, class Alloc = allocator<T>>
T:set存放的元素类型，实际在底层存储pair<T, T>键值对，及key和value一样
Compare<T>:仿函数，set存放元素的顺序，默认按照小于来比较，输出为升序(中序遍历输出为升序)
Alloc:空间配置器，在所有容器中都会有这样子一个参数，加快向申请内存的效率	*/

//set的每个value都是唯一的，并且set中的元素不能修改(元素总是const)，但是可以插入和删除
//set容器通过key访问单个元素的速度通常比unordered_set容器慢，但他们允许根据顺序对子集进行直接迭代
//将数据放入set，他可以字段帮我们完成排序+去重的工作

void test()
{
	//构造函数
	//set(const Compare& cmp = Compare())
	//set<int> s1(std::less<int>());	//error，虽然函数模板里面确实有Compare这个类型的参数，但是set容器模板里面也存在Compare
	//而且函数模板里面的Compare是依赖于set容器的，并且set容器的模板已经有默认的参数类型less<int>，所以不能在函数模板里面重新指定
	//这也说明了list容器中的那个问题(这个问题有点像函数定义和声明的参数都存在缺省值一样)

	//正确写法
	set<int, std::less<int>> s1;
	set<int> s2;

	//set(InputIterator first, InputIterator last, const Compare& cmp = Compare())
	set<int> s3(s2.begin(), s2.end());

	//set(const set<T>& s)
	set<int> s4(s3);

	//其他
	set<int> s5 = { 1,2,3,4,5 };

	//set的迭代器
	//iterator begin():返回容器起始位置元素迭代器
	set<int>::iterator it = s1.begin();

	//iterator end():返回容器中最后一个元素后面的迭代器
	
	//const_iterator cbegin() const:返回容器中起始位置元素的const迭代器
	set<int>::const_iterator c_it = s1.cbegin();

	//const_iterator cend() const:返回容器中最后一个元素后面的const迭代器

	//reverse_iterator rbegin():返回最后一个元素的反向迭代器
	set<int>::reverse_iterator r_it = s1.rbegin();

	//reverse_end() rend():返回容器第一个元素的前一个位置的迭代器

	//const_reverse_iterator crbegin() const:返回容器中最后一个元素的方向const迭代器
	set<int>::const_reverse_iterator cr_it = s1.crbegin();

	//const_reverse_iterator crend() const:返回容器中第一个元素的前一个位置的反向迭代器


	//empty()
	cout << set<int>().empty();		//1

	//size():返回set中有效元素个数
	s1.size();

	//pair<iterator, bool> insert(const T& val):在容器中插入val值(实际是插入<val, val>键值对)
	//插入成功返回<该元素在容器的位置(迭代器), true>，插入失败，说明val已经存在，返回<val在容器中的迭代器, false>
	pair<set<int>::iterator, bool> p1 = s1.insert(10);
	//set容器里面没有push函数，只有insert函数

	//void erase(iterator pos):删除容器中pos位置上的元素，pos必须是有序迭代器
	//如果pos是通过find找到的，那么在删除前检查一下是否==set::end，如果pos不是有效位置，删除会报错
	s1.erase(s1.begin());

	//size_t erase(const T& val):删除容器中值为val的元素，返回删除的元素个数，如果val不存在不会报错(即返回值只有0或1)
	size_t count = s1.erase(10);

	//void erase(iterator first, iterator last):删除[first, last)区间的元素

	//void swap(set<T>& s):交换两个容器

	//void clear():清空容器

	//size_t count(const T& val) const:返回容器中值为val的元素个数

	//iterator find(const T& val) const:返回set中val元素的迭代器，找不到返回set::end()
	set<int>::iterator f_it = s1.find(10);
}

//set容器里面的find比算法库里面的find快，测试如下:
void test()
{
	srand((size_t)time(nullptr));
	set<int> s;
	for (size_t i = 0; i < 10000; i++)
	{
		s.insert(rand());
	}
	cout << "插入元素个数:" << s.size() << endl;
	int begin1 = clock();
	for (auto e : s)
	{
		s.find(e);
	}
	int end1 = clock();
	for (auto e : s)
	{
		find(s.begin(), s.end(), e);
	}
	int end2 = clock();
	cout << "容器的find()函数用时:" << end1 - begin1 << endl;
	cout << "算法库的find()函数用时:" << end2 - end1;
}



//multiset
//multiset允许插入重复值，其余和set的使用相同

//对于重复值的处理:查找一个重复出现的值，multiset返回第一个插入multiset容器的值的迭代器
//使用erase函数时会删除所有重复值
void test()
{
	multiset<int, std::less<int>> m;

	multiset<int> ms;
	ms.insert(10);
	ms.insert(5);
	ms.insert(10);
	ms.insert(15);
	ms.insert(10);

	multiset<int>::iterator it = ms.find(10);
	cout << (it == ms.begin()) << endl;		//1

	ms.erase(10);
	for (auto e : ms)
	{
		cout << e << " ";
	}		//5 15
}


//map
//容器模板参数
//template<class key, class value, class Compare& = less<key>>

/*map使用关联式容器，每个元素为键值和映射值的组合，元素之间符合特定的次序
map中key值用来排序以及唯一标识元素，value中存储与键值key关联的内容。键值key和值value的类型可能不同
map中的value值可能有重复，但是key值唯一，在内部，map中的元素总是按照键值key进行比较排序的(排序的方式就是仿函数less和greater)
map中通过键值访问单个元素的速度通常比unordered_map容器慢，但map允许根据顺序对元素进行直接迭代(即对map中的元素进行迭代时，可以得到一个有序的序列)
map支持下标访问符，即在[]中放入key，就可以找到与key对应的value。key值在map里是唯一的	*/

//map函数接口
void test()
{
	//构造函数
	//map(const Compare& = Compare())
	map<int, string> m1;
	map<int, string, greater<int>> m11;

	//map(InputIterator first, InputIterator last, const Compare& cmp = Compare())
	map<int, string> m2(m1.begin(), m1.end());

	//map(const map& m)
	map<int, string> m3(m2);

	//map的迭代器和set类似，但是注意:得到迭代器后，需要用箭头来获取pair的first(键值)和value(实值)
	map<int, string>::iterator it = m1.begin();
	cout << it->first << " " << it->second << endl;

	//size():返回容器有效元素个数

	//empty():判断容器是否为空

	//pair<iterator, bool> insert(const pair<key, value>& p)
	m3.insert(pair<int, string>(1, "Tom"));		//调用匿名对象
	m3.insert(make_pair(2, "Jerry"));			//使用make_pair函数(常用)
	//插入成功，返回插入元素的迭代器和true，插入失败说明元素已经在map中存在，返回map中键值为key的迭代器和false

	//iterator find(const key& k):输入key值就可以查找，没有找到返回map::end()

	//size_t count(const key& k) const:只用输入key值就可以得到key在容器的个数

	//size_t erase(const key& k):删除指定的key值的元素，删除不成功不会报错，返回删除元素个数

	//void erase(iterator pos):删除指定迭代器位置所在的元素，删除不成功会报错

	//swap():交换两个map容器
}

//map的[]函数重载(重点)
//value& operator[](const key& k):其函数参数就是key值
//[]重载函数的返回值为:(*((this->insert(make_pair(k, value()))).first).second
/*具体理解如下:
1. 调用insert函数插入键值对
2. 拿出从insert函数获取到的迭代器
3. 返回该迭代器位置元素的值value	*/

//代码分析如下
template<class key, class value>
value& operator[](const key& k)
{
	pair<iterator, bool> ret = this->insert(make_pair(k, value()));		//通过insert函数找到k的迭代器地址
	iterator it = ret.first;		//获取k的迭代器
	return it.second;			//返回value值
}

//函数的妙用
void test()
{
	map<int, string> m;
	m.insert(make_pair(1, "one"));
	m.insert(make_pair(2, "two"));
	m.insert(make_pair(3, "three"));

	m[2] = "Tom";		//修改key值为2的元素的value值

	m[6] = "six";		//插入键值对(6, "six")
	//上面的返回结果是插入键值对(6, "six")后对value的引用

	for (auto e : m)
	{
		cout << e.first << "->" << e.second << endl;
	}
}


//multimap
//multimap和map的区别和multiset和set的区别一样，multimap允许键重复
//multimap和map的函数接口基本一致，这里只介绍一些有差异的成员函数
void test()
{
	//find(const key& k):返回第一个插入的键值为key的元素迭代器
	multimap<int, string> mmp;
	mmp.insert(make_pair(1, "one"));
	mmp.insert(make_pair(2, "two"));
	mmp.insert(make_pair(1, "Tom"));

	map<int, string>::iterator it = mmp.find(1);
	cout << it->second;		//one

	//size_t count(const key& k):返回键值为k的元素个数

	//注意：由于multimap容器允许键值冗余，调用[]运算符重载函数时，返回值存在歧义，所以multimap没有实现[]运算符重载
}


//map和set模拟实现的测试
#include "map-set.h"
int main()
{
	yw::set<string> s;
	s.insert("张三");
	s.insert("李四");
	s.insert("王五");
	yw::set<string>::iterator s_it = s.find("张三");
	cout << *s_it << endl;
	s.erase("张三");
	for (auto e : s)
	{
		cout << e << endl;
	}

	yw::map<string, int> m;
	m.insert(make_pair("张三", 1));
	m.insert(make_pair("李四", 2));
	m.insert(make_pair("王五", 3));
	yw::map<string, int>::iterator ret = m.find("李四");
	cout << ret->second << endl;
	m.erase("张三");
	m["赵六"] = 1;
	for (auto e : m)
	{
		cout << e.first << ":" << e.second << endl;
	}
	return 0;
}
