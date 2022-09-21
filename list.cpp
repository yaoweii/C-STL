#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <cassert>
using namespace std;
/*list������
1. list�ǿ����ڳ�����Χ��������λ�ý��в����ɾ��������ʽ���������Ҹ���������ǰ��˫�����
2. list�ĵײ���˫������ṹ��˫��������ÿ��Ԫ�ش洢�ڻ�����صĶ����ڵ��У��ڽڵ���ͨ��ָ��ָ����ǰһ��Ԫ�غͺ�һ��Ԫ��
3. list��forward_list�ǳ����ƣ�����Ҫ�Ĳ�ͬ����forward_list�ǵ�����ֻ�ܳ�ǰ��������������򵥸�Ч
4. ������������ʽ�������(array��vector��deque)��listͨ��������λ�ý��в��롢�Ƴ�Ԫ�ص�ִ��Ч�ʸ���
5. ����������ʽ������ȣ�list��forward_list����ȱ���ǲ�֧������λ�õ��������
	���磺Ҫ����list�ĵ�6��Ԫ�أ��������֪��λ��(����ͷ������β��)��������λ�ã������λ���ϵ�����Ҫ���Ե�ʱ�俪��
	list����ҪһЩ����Ŀռ䣬�Ա���ÿ���ڵ���������Ϣ(���ڴ洢���ͽ�СԪ�صĴ�list��˵�������һ����Ҫ������
6. list�����ɾ������Ԫ�ض�������ɸõ�����ʧЧ�������ַ���䣬��Ϊ����ͨ��next��prevָ�������ʣ��������vector��ͬ
7. ����list�Ĵ���ռ䲻�������ģ����Ե�����ֻ��ǰ���ƶ�(����++��--)�����ʣ�����*(pos + n)����  */

template<class T>
struct down
{
	bool operator()(T val1, T val2)
	{
		return val1 > val2;
	}
};

//list�����ĳ��ýӿڽ���
void test()
{
	//���캯��
	//list():���������
	list<int> st1;
	cout << st1.size();		//0

	//lsit(size_t n, const T& val = T())
	list<int> st2(10, 100);

	//lsit(Inputiterator first, Inputiterator last)
	list<int> st3(st2.begin(), st2.end());

	//list(const list& st)
	list<int> st4(st1);

	//����
	list<int> st5 = { 9,8,7,6,5,4 };
	
	//������
	list<int>::iterator it = st1.begin();		//���ص�һ��Ԫ�صĵ�����
	list<int>::iterator it = st1.end();			//�������һ��Ԫ�ص���һ��λ�õĵ�����(ʵ�������ڱ�λ�ĵ�����)
	list<int>::const_iterator c_it = st1.cbegin();
	list<int>::reverse_iterator r_it = st1.rbegin();	//�������һ��Ԫ�صĵ�����
	list<int>::reverse_iterator r_it = st1.rend();		//���ص�һ��Ԫ�ص�ǰһ��λ�õĵ�����(ʵ���Ͼ����ڱ�λ)
	list<int>::const_reverse_iterator c_r_it = st1.crbegin();
	//ע�⣺�����const�������rbegin����ô���ص���const���͵ķ��������(��������Ҳһ��)

	//ע�⣺�Է��������ִ��++��������������ǰ��
	list<int> test = { 1,2,3,4,5 };
	for (list<int>::reverse_iterator r_it = test.rbegin(); r_it != test.rend();)
	{
		cout << *r_it << ' ';
		r_it++;
	}			//5 4 3 2 1

	//empty():�ж��Ƿ�Ϊ��
	cout << list<int>().empty();		//1

	//size():����list����Ч���ݸ���
	cout << st1.size();

	//list��û��capacity()�ӿڣ���Ϊ����һ�����ݾͿ���һ���ռ�

	//front():����list�е�һ���ڵ��ֵ�����û�о��׳��쳣
	cout << st1.front();

	//back():�������������һ���ڵ��ֵ�����û���׳��쳣
	cout << st1.back();

	//push_back():β��
	st1.push_back(2);

	//pop_back():βɾ�����ֻ��ͷ��������׳��쳣
	st1.pop_back();

	//push_front():ͷ��
	st1.push_front(2);

	//pop_front():ͷɾ�����ֻʣͷ������׳��쳣
	st1.pop_front();

	//iterator insert(iterator pos, const T& val):�ڵ�����pos֮ǰ����val�����ز���λ�õĵ�����
	st1.insert(st1.begin(), 2);

	//iterator erase(iterator pos):ɾ��posλ�õ�����
	//iterator erase(iterator first, iterator last):ɾ����������������ݣ�����ҿ�[first,last)����������Ҳ��һ��
	list<int>::iterator it = find(st1.begin(), st1.end(), 2);		//����find�÷���vector��һ���������㷨�������
	st1.erase(it);
	st1.erase(st1.begin(), st1.end());

	//swap():��������list������ʵ���Ͼ��ǽ���ͷ����ָ��
	st1.swap(st2);

	//clear():���list�е�����Ԫ��
	st1.clear();
	cout << st1.empty();	//1

	//operator=
	st1 = st2;

	//remove(const T& val):���list�����е�valֵ
	st1 = { 1,2,2,2,3 };
	st1.remove(2);
	for (auto e : st1)
	{
		cout << e << ' ';
	}		//1 3

	//splice():��һ����������ָ��λ�õĵ�����ת�Ƶ���һ����������
	//splice(iterator pos, list& st):��st�����������������ת�Ƶ����øú����Ķ�����pos��������ǰ��
	st1 = { 1,3,5,7 };
	st2 = { 2,4,6,8 };
	list<int>::iterator it = find(st1.begin(), st1.end(), 2);
	st1.splice(it, st2);
	for (auto e : st1)
	{
		cout << e << " ";
	}						//1 2 4 6 8 3 5 7
	//��ʱst2�ѽ����˿�����

	//splice(iterator pos1, list& st, iterator pos2):��st������pos2λ�õĵ������Ƶ����øú����Ķ�����pos1λ�õ�������ǰ��
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

	//sort():����������Ĭ������(���Ƽ�ʹ�ã�Ч�ʵͣ��������罫���ݿ�����vector������ٿ�����listЧ�ʸ�)
	st1 = { 1,5,4,9,6,3 };
	st1.sort();
	for (auto e : st1)
	{
		cout << e << " ";
	}						//1 3 4 5 6 9

	//����д��(ʹ�÷º���)
	down<int> down;
	st1.sort(down);

	//assign(iterator begin, iterator end):��[begin,end)�����ֵ��������
	st2.assign(st1.begin(), st1.end());

	//assign(size_t n, T& val)
	st2.assign(10, 100);

	//resize(size_t n, T& val = T())
	st1.resize(100);
	//list�����ǲ���һ��Ԫ�زŻᴴ���ڴ�ռ䣬����resize�����ʼ��(һ��list��������ʹ��resize)

	//reverse():��ת����
	st1.reverse();
}


//list������ʧЧ
void test()
{
	//list������˫������ṹ�����Բ���Ԫ��ʱ���ᵼ��list������ʧЧ
	//��Ϊlist�ռ䲻������������Ų�����ݵ����
	//����ֻ��ɾ��ʱ�Ż�ʧЧ������ʧЧ��ֻ��ָ��ɾ���ڵ�ĵ�����

	list<int> st = { 1,2,3,4,5,6 };
	for (list<int>::iterator it = st.begin(); it != st.end();)
	{
		st.erase(it);
		//it++;		//erase��ԭit��������ʧЧ�ˣ�����ʹ�õ�����++��
		//��Ϊ����++�����صģ����ǿ��Խ�it���Ϊһ������++�����Ǽ򵥵ĵ�ַ��ǰ�ƶ�

		//��ȷ����
		//1.���¸�it��ֵ
		it = st.begin();
		//2.
		st.erase(it++);		//����Ҫ�ο�listģ��ʵ���еĺ���++ʵ�ֺ�eraseʵ��
	}
}


//�㷨����
//sort(st1.begin(), st1.end());		//error
//sort����ʱ�������򣬱���֧�������ȡ�����ݽṹ����ʵ�֣���list�ռ䲻�������ģ���֧���������

//������
//����һ���࣬�Ȱ����������ٰ����ֽ���
class Person {
public:
	int age;
	string name;
	int high;
	Person(string name,int age,int high):name(name),age(age),high(high){}
};
//ָ��������򣨻ص�����:������Ϊ�������������ĺ�����������Ҳ����д�ɷº���
bool compare(Person& p1, Person& p2)
{
	//������������
	if (p1.age == p2.age)
	{
		//���������ͬ���������ֽ���
		return p1.name > p1.name;
	}
	return p1.age < p2.age;
}
int main()
{
	list<Person> L1(5);
	//��������
	Person p1("����", 50, 176);
	Person p2("����", 40, 180);
	Person p3("�ŷ�", 35, 180);
	Person p4("��", 40, 190);
	Person p5("����", 35, 188);
	Person p6("�����", 55, 170);
	//��������
	L1.push_back(p1);
	L1.push_back(p2);
	L1.push_back(p3);
	L1.push_back(p4);
	L1.push_back(p5);
	L1.push_back(p6);

	L1.sort();		//error����������֪����ô����
	//ָ���������
	L1.sort(compare);
	return 0;
}


//listģ��ʵ�ֵĲ���
#include "list.h"
using namespace std;
int main()
{
	yw::list<string> st1;
	st1.push_back("����");
	st1.push_front("����");
	st1.insert(st1.begin(), "����");

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

//���ڵ�������->��ʹ��
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
	it->day;				//��Ȼ->���ص������ݵ�ָ�룬��Ҳ����ֱ�ӷ��ʵ�������ĳ�Ա����
	it.operator->()->day;	//�����Ӳŷ������غ���ʵ�ֵ��߼�(�����ص������ݵ�ָ��)
	st.clear();
}