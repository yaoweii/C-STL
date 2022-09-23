#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <list>
using namespace std;

//priority_queue的介绍
/*优先级队列默认使用vector作为其底层存储数据的容器，在vector上又使用了堆算法将vector中元素构造成堆的结构
因此priority_queue就是堆，所有需要用到堆的位置，都可以考虑使用priority_queue
注意：默认情况下priority_queue是大堆(关于大堆和小堆的排序算法具体可以看一下数据结构里面的堆排序)

1、优先队列是一种容器适配器，根据严格的弱排序标准，它的第一个元素总是它所包含的元素中最大的(默认是建大堆)
2、在堆中可以随时插入元素，并且只能检索最大堆元素(优先队列中位于顶部的元素)
3、优先队列被实现为容器适配器，即将特定容器类封装作为其底层容器类，priority_queue提供一组特定的成员函数来访问其元素
元素从特定容器的“尾部”弹出，其称为优先队列的顶部
4、底层容器可以是任何标准容器类模板，也可以是其他特定设计的容器类。底层容器应该可以通过随机访问迭代器访问，并支持以下操作：
empty()：检测容器是否为空				size()：返回容器中有效元素个数
front()：返回容器中第一个元素的引用		push_back()：在容器尾部插入元素
pop_back()：删除容器尾部元素
5、标准容器类vector和deque满足这些需求。默认情况下，如果没有为特定的priority_queue类实例化指定容器类，则使用vector
6、底层容器需要支持随机访问迭代器，以便始终在内部保持堆结构。
容器适配器通过在需要时自动调用算法函数make_heap、push_heap和pop_heap来自动完成此操作 
7、priority_queue不支持遍历，也没有迭代器
8、priority_queue包含在queue头文件中	*/


//priority_queue的常用接口
void test()
{
	//构造函数
	//priority_queue(const Compare& comp = Compare(), const Container& con = Container()):无参构造，构造一个空的队列
	priority_queue<int> q1;

	/*priority_queue(InputIterator first, InputIterator last,
	const Compare& comp = Compare(), const Container& con = Container()):迭代器构造
	注意:这个迭代器是普通迭代器(inputIterator)，说明我们可以传vector、list...这样的迭代器*/
	vector<int> vtr = { 1,2,3,4,5 };
	priority_queue<int> q2(vtr.begin(), vtr.end());

	list<int> st = { 10,20,30,40,50 };
	priority_queue<int> q3(st.begin(), st.end());

	//传数组地址也可以
	int arr[] = {3,4,2,1,5};
	priority_queue<int> q4(arr, arr + 5);

	//注意：因为priority_queue是建大堆，所以传入的数据顺序和存储数据顺序不一样

	/*介绍priority_queue的三个模板参数
	template<class T, class Container = vector<T>, class Compare = less<typename Container::value_type>>

	1. class T:表示存储元素的数据类型
	2. class Container = vector<T>:表示底层容器
	3. class Compare = less<typename Container::value_type>:仿函数，不传时默认建大堆，如果建小堆需要指明并且引入头文件#include <functional>
	这里的value_type就是底层容器的数据类型T	*/

	priority_queue<int> q5(greater<int>(), deque<int>());
	priority_queue<int, deque<int>, greater<int>> q6;

	priority_queue<int, deque<int>, greater<int>> q7(vtr.begin(), vtr.end());

	//priority_queue<int> q8(vtr.begin(), vtr.end(), greater<int>());		//error
	//priority_queue<int> q9(vtr.begin(), vtr.end(), greater<int>(), vector<int>());		//error
	/*上面两个例子是错误的，这是因为类模板的成员函数只有在成员函数只会在类实例化后实例化
	这就意味着，如果我们前只指定了int，那么其他两个模板参数就是默认模板参数，即vector<T>和less<T>，所以生成的函数的参数类型就是这两个
	而我们调用函数时用的参数为greater<T>，此时就会找不到该函数重载，直接报错，下面这两个例子就不会报错，因为实例化的模板函数参数类型与下面一致	*/
	priority_queue<int> q8(vtr.begin(), vtr.end(), less<int>(), vector<int>());
	priority_queue<int> q9(vtr.begin(), vtr.end(), less<int>());	
	//总结：建议直接在容器的模板里面声明参数类型，不要在调用模板成员函数时再去声明类型，如下
	priority_queue<int, deque<int>, greater<int>> q10(vtr.begin(), vtr.end());

	//empty():判断队列是否为空
	cout << q1.empty();

	//top():返回优先队列的堆顶元素(实际上就是底层数组的第一个元素，也就是整个队列(大堆)中最大的数)
	cout << q1.top();

	//push():插入元素，插入后可能某些元素的位置就会发生变化(即堆发生变化)
	q1.push(10);
	//注意：建立堆 != 排序，只要满足堆的特点即可(所以不一定会是排序后的样子)
	
	//pop():删除堆顶的元素(删除后会重新建堆)
	q1.pop();

	//size():返回队列元素个数
	cout << q1.size();

	//swap():交换两个优先队列的顺序
	q1.swap(q2);
}


/*总结：
1、less对应建大堆，也是默认的。 我们在实现仿函数时，内部用小于号 <
   greater对应建小堆，我们在实现仿函数时，内部用大于号 >
2、我们要在priority_queue中存放自定义类型时，用户需要在自定义类型中提供 > 或者 < 的重载
最好也可以把仿函数自己实现，因为有时候像存储Date*这样的类型时，可能会出现问题，案例如下
建大堆时：大堆，需要用户在自定义类型中提供<的重载  口诀：大堆->less->小于号
建小堆时：小堆，需要用户提供>的重载  口诀：小堆->greater->大于号		*/

#include "priority_queue.h"
using yw::Date;
void test()
{
	yw::priority_queue<Date*, vector<Date*>, greater<Date*>> q;
	q.push(new Date(2022, 8, 25));
	q.push(new Date(2022, 5, 6));
	q.push(new Date(2022, 7, 20));
	q.push(new Date(2022, 6, 15));
	while (!q.empty())
	{
		cout << *q.top();
	}
	//此时我们发现我们打印出来的结果并不是一个堆结构
	/*原因：因为这里我们如果没有自定义greater函数，那么这里推导出来类型为Date*后
	就会走库里面的greater函数，从而进行两个地址的比较，这样就和我们想要的结果不符*/

	//正确做法:在greater函数前面加上域名yw::，表示函数不是functional库里面的，而是自定义的
	yw::priority_queue<Date*, vector<Date*>, yw::greater<Date*>> q;
}


//priority_queue的模拟实现测试
int main()
{
	yw::priority_queue<string> pq;
	pq.push("张三");
	cout << pq.size() << endl;
	cout << pq.top() << endl;
	cout << pq.empty() << endl;
	pq.pop();
	cout << pq.empty() << endl;
	return 0;
}
