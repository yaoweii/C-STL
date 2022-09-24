#include <map>
#include <iostream>
using namespace std;

//对组pair
/*pair是将2个数据组合成一组数据，如stl中的map就是将key和value放在一起来保存，或者当一个函数需要返回2个数据的时候，也可以选择pair
pair的实现是一个结构体，主要的两个成员变量first和second，分别存储两个数据	*/

void test()
{
	//pair的三个初始化方式
	pair<int, string> p1(1, "Tom");
	pair<int, string> p2 = make_pair(2, "Jerry");		//注意:当我们函数使用make_pair作为返回值或者参数时不能作为引用，当make_pair作为函数参数时，需要用const接收
	pair<int, string> p3;
	p3.first = 3;
	p3.second = "Beken";

	//pair<int, string> p4 = (4, "Jhon");		//error
}

//pair模拟实现
namespace yw
{
	template<class K, class V>
	struct pair
	{
		K first;
		V second;

		pair(const K& = K(), const V& = V()) :first(K), second(V)
		{}

		~pair(){}

		pair(const pair<K, V>& p)
		{
			first = p.first;
			second = p.second;
		}

		pair<K, V>& operator=(const pair<K, v>& p)
		{
			if (&p != this)
			{
				first = p.first;
				second = p.second;
			}
			return *this;
		}
	};

	//make_pair函数实现
	template<typename T1, typename T2>
	pair<T1, T2> make_pair(T1& x, T2& y)
	{
		return yw::pair<T1, T2>(x, y);		//返回匿名对象
	}
}

void test()
{
	yw::pair<int, string> p1(1, "tom");
	yw::pair<int, string> p2 = p1;
	p2.first = 2;
}