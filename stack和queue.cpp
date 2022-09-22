#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <deque>
using namespace std;

/*stack
1. stack是一种容器适配器，专门用在具有后进先出操作的上下文环境中，其删除只能从容器的一端进行元素的插入与提取操作
2. stack是作为容器适配器被实现的，容器适配器即是对特定类封装作为其底层的容器，并提供一组特定的成员函数来访问其元素
将特定类作为其底层，元素特定容器的尾部(即栈顶)被压入和弹出
3. stack的底层容器可以是任何标准的容器类模板或者一些其他特定的容器类，这些容器类应该支持以下操作：
empty：判空操作						back：获取尾部元素操作
push_back：尾部插入元素操作			pop_back：尾部删除元素操作
4. 标准容器vector、deque、list均符合这些需求，默认情况下，如果没有为stack指定特定的底层容器，默认情况下使用deque */


//stack的函数接口
void test()
{
	//构造函数
	//stack(const container_type& con = container_type())
	//这里的container_type就是适配器，默认为deque
	stack<int> sk1;

	stack<int, vector<int>> sk3;		//指定底层容器为vector

	stack<int> sk2(sk1);

	//operator=(const stack<T>& sk)
	sk2 = sk1;

	//push(T val):压栈
	sk1.push(10);

	//pop():出栈
	sk1.pop();

	//top():返回栈顶元素
	int ret = sk1.top();

	//empty():判断栈是否为空
	sk1.empty();

	//size():返回栈中储存元素个数
	sk1.size();

	//swap():交换两个栈的数据
	sk1.swap(sk2);
}


/*queue
1. 队列是一种容器适配器，专门用于在FIFO上下文(先进先出)中操作，其中从容器一端插入元素，另一端提取元素(尾插，头删)
2. 队列作为容器适配器实现，容器适配器即将特定容器类封装作为其底层容器类，queue提供一组特定的成员函数来访问其元素
元素从队尾入队列，从队头出队列
3. 底层容器可以是标准容器类模板之一，也可以是其他专门设计的容器类。该底层容器应至少支持以下操作:
empty：检测队列是否为空			size：返回队列中有效元素的个数
front：返回队头元素的引用		back：返回队尾元素的引用
push_back：在队列尾部入队列		pop_front：在队列头部出队列
4. 标准容器类deque和list满足了这些要求。默认情况下，如果没有为queue实例化指定容器类，则使用标准容器deque	*/

//queue常用接口
void test()
{
	//构造函数
	//queue(const container_type& con = container_type())
	queue<int> qu1;
	queue<int, list<int>> qu2;

	//queue(const queue<T>& qu)
	queue<int> qu3(qu1);

	//queue<T>& operator=(const queue<T>& que)
	qu1 = qu3;

	//push():入队
	qu1.push(10);

	//pop():出队，将队头的元素进行删除，头结点除外
	//注意：因为queue的底层是list或deque，所以其底层实现是有一个头结点的，只是queue将其封装了
	qu1.pop();

	//front():返回队头元素的引用(注意如果这里不加const是可以修改队列中的元素数据的)
	int ret = qu1.front();

	//back():返回队尾元素的引用(这里和上面一样，同样可以修改ret来修改队列中的元素数据)
	ret = qu1.back();

	//empty()：判断是否为空
	qu1.empty();

	//size()：返回队列元素个数
	qu1.size();

	//swap():交换队列中的数据(本质就是交换头结点)
	qu1.swap(qu3);
}

//总结：容器中的back()、front()、at()函数返回的都是引用


//stack和queue模拟实现的测试
#include "stack-queue.h"
int main()
{
	yw::stack<string, vector<string>> sk;
	sk.push("张三");
	sk.push("李四");
	sk.pop();
	cout << sk.top() << endl;
	cout << sk.size() << endl;
	cout << sk.empty() << endl;

	yw::queue<string, list<string>> qu;
	qu.push("Tom");
	qu.push("Jerry");
	cout << qu.back() << endl << qu.front() << endl << qu.size() << endl;
	cout << qu.empty() << endl;
	qu.pop();
	cout << qu.front() << endl;
	return 0;
}