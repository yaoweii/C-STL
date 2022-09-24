#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
#include <ctime>
using namespace std;
//deque就是一个双端数组，可以进行头部的插入和删除
/*deque和vector的区别：
vector对于头部的插入删除效率低，数据量越大，效率越低，deque相对而言，对头部的插入删除速度回比vector快

vector访问元素时的速度会比deque快,这和两者内部实现有关
deque 的内部实现原理：
在deque容器的内部有一个中控器的东西，来管理每一小段的数组，数组里面存放真实数据，而中控器存放的是每一小段数组的首地址
当你要头插数据的时候，它会在中控器中寻找，找第一个数组看看是否头部可以插入数据，假如可以就在找到的位置插入
没有的话，就会重新开辟一段内存，指向数组，插入数据。删除头部也是一样。每一段小数组都是连续的，因为中控器的地址也是连续的，使得deque像一个连续的空间
访问数据不那么快的原因是因为：需要从中控器中找到地址，在去访问数组的元素，导致有点慢	

deque的内部结构：http://t.csdn.cn/j5LyR	*/


//deque常用函数接口
void test()
{
	//构造函数
	//deque():默认构造
	deque<int> dq1;

	//deque(InputIterator first, InputIterator last):将[first, last)空间的数据拷贝给deque对象
	deque<int> dq2(dq1.begin(), dq1.end());

	//deque(size_t n, T& val = T()):将n个val数据给deque对象
	deque<string> dq3(10, "张三");

	//deque(const deque<T>& dq):拷贝构造函数
	deque<string> dq4(dq3);

	//其他
	deque<int> dq5 = { 1,2,3,4,5 };

	//赋值操作
	//deque<T>& operator=(const deque<T>& dq)
	dq3 = dq4;

	//assign(InputIterator first, InputIterator last):将[first, last)区间的值拷贝到本身
	dq3.assign(dq4.begin(), dq4.begin() + dq4.size());
	//注意：deque的迭代器是支持加随机值的，不只是++和--(这里的 迭代器 + 任意数 的+也是重载的)

	//assign(size_t n, T& val = T()):将n个val数据拷贝给本身
	dq3.assign(10, "Tom");
	//注意：assign函数会将原来容器里面的数据删除

	//empty():判断是否为空，是空返回true
	cout << dq3.empty() << endl;			//0

	//size():返回deque容器的数据个数
	size_t count = dq3.size();

	//resize(size_t num, cosnt T& val):将size置为num，如果num > szie，那么扩容，超出部分赋值为val，如果小于则尾删超出部分
	dq3.resize(20);
	//deque容器没有capacity概念，可以无限扩容

	//push_back(T& val):尾插
	dq3.push_back("TiMi");

	//pop_back():尾删
	dq3.pop_back();

	//push_front():头插
	dq3.push_front("IT");

	//pop_front():头删
	dq3.pop_front();

	//insert(const_iterator pos, T& val):指定迭代器pos前插入val，返回插入数据的位置
	dq2.insert(dq2.begin(), 100);

	//insert(const_iterator pos, size_t n, T& val):指定迭代器pos前插入n个val数据
	dq2.insert(dq2.begin() + dq2.size(), 2, 100);

	//insert(const_iterator pos, InputIterator first, InputIterator last):在pos位置前插入[first, last)区间的值
	dq1.insert(dq1.begin(), dq2.begin(), dq2.end());

	//clear()		//清空所有数据
	dq3.clear();

	//erase(iterator begin, iterator end):删除[begin, end)区间的元素，返回下一个数据的迭代器
	dq1.erase(dq1.begin(), dq1.begin() + 1);

	//erase(pos):删除pos位置数据，返回下一个数据的迭代器
	dq2.erase(dq2.begin());

	//T& operator[](size_t n)
	dq2[2] = 50;

	//T& at(size_t n)
	dq1.at(0) = 50;

	//T& front():返回容器第一个元素
	dq1.front();

	//T& back():返回容器最后一个元素
	dq2.back();


	//deque容器的排序
	dq1.resize(0);
	for (int i = 10; i >= 0; i--)
	{
		dq1[i] = i;
	}
	//默认排序规则是升序
	sort(dq1.begin(), dq1.end());	//需要引入标准算法头文件
	//对于可以随机访问的迭代器，都可以利用sort算法对其进行排序，例如vector

	for (auto e : dq1)
	{
		cout << e << " ";
	}			//0 1 2 3 4 5 6 7 8 9 10
}


//案例：五名选手ABCDE，十个评委打分，去掉最高分去掉最低分
class Person {
public:
	string name;
	int score;
	Person(string name, int score):name(name),score(score){}
};
void CreatPerson(vector<Person>& v)
{
	string ch = "ABCDEF";
	for (int i = 0; i < v.size(); ++i)
	{
		string name = "选手";
		name += ch[i];
		int score = 0;
		Person p(name, score);
		//将创建的Person对象放入容器中
		v.push_back(p);
	}
}
void SetScore(vector<Person>& v)
{
	for (int i = 0; i < v.size(); ++i)
	{
		//将评委的分数放到deque容器中
		deque<int>Score(10);
		for (int i = 0; i < Score.size(); ++i)
		{
			srand(time(NULL));
			int score = rand() % 41 + 60;		//设置一个60-100的分数
			Score.push_back(score);
		}
		sort(Score.begin(), Score.end());
		Score.pop_back();
		Score.pop_front();
		int cout = 0;
		for (int i = 0; i < Score.size(); ++i)		//计算每个人的总分
		{
			cout += Score[i];
		}
		cout = cout / (float)Score.size();		//计算平均分
		v[i].score = cout;			//将平均分放到每个人的score成员中
	}
}
void PrintScore(vector<Person>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i].name << "的分数为" << v[i].score << endl;
	}
}
int main()
{
	//创建五名选手
	vector<Person> vtr(5);
	//选手初始化
	CreatPerson(vtr);
	//设置分数
	SetScore(vtr);
	//打印每个选手的平均分
	PrintScore(vtr);
	return 0;
}