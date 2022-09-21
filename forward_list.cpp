#include <iostream>
#include <string>
#include <forward_list>
using namespace std;

/*forward_list容器就是一个单向链表，具有和list容器相同的特性，即擅长在序列的任何位置进行插入元素或删除元素的操作
另外，由于单链表没有双向链表那样灵活，因此相比list容器，forward_list容器的功能受到了很多限制
比如，由于单链表只能从前向后遍历，而不支持反向遍历，因此 forward_list 容器只提供前向迭代器，而不是双向迭代器
这意味着，forward_list容器不具有rbegin()、rend()之类的成员函数

forward_list优点:存储相同个数的同类型元素，单链表耗用的内存空间更少，空间利用率更高，并且对于实现某些操作单链表的执行效率也更高
效率高是选用forward_list而弃用list容器最主要的原因，换句话说,只要是list容器和forward_list容器都能实现的操作，应优先选择forward_list容器	*/

//forward_list的常用函数接口
void test()
{
	//forward_list()
	forward_list<int> fst1;

	//before_begin():返回哨兵位的迭代器
	forward_list<int>::iterator b_it = fst1.before_begin();

	//begin():返回第一个元素的迭代器
	//end():返回最后一个元素的下一个位置的迭代器(不是哨兵位，而是会创建一个值为0的迭代器返回)

	//empty():判断容器是否为空，是空返回true

	//T& front():返回第一个元素(可以修改)
	int val = fst1.front();

	//assign(InputIterator first, InputIterator last)
	//assign(size_t n, T& val = T())
	//assign函数会覆盖原容器的数据

	//push_front()
	fst1.push_front(10);

	//pop_front()
	fst1.pop_front();

	//clear()

	//resize(size_t n, const T& val = T())
	fst1.resize(10);

	//insert_after(iterator pos, T& val):在pos后面插入元素val
	fst1.insert_after(fst1.begin(), 10);

	//erase_after(iterator pos):删除pos后面的数据
	fst1.erase_after(fst1.begin());

	//remove(T& val):删除容器中所有等于val的元素
	fst1.remove(10);

	//swap(forward_list<T>& fst):交换两个容器的元素(就是交换头结点)

	//merger(const forward_list<T>& fst):合并两个有序forward_list容器，并且保证合并后依然有序

	//sort():排序(默认升序)

	//reverse():反转链表

	//我们发现forward_list没有size()函数，如果想要或者容器的size，可以使用头文件中的distance()函数
	forward_list<int> fst2 = { 1,2,3,4,5 };
	cout << distance(fst2.begin(), fst2.end());			//5

	//forward_list容器和list一样也不支持随机访问，迭代器只能++或者--，不能 +或- 随机值
}