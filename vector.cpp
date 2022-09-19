#include <iostream>
#include <vector>			//ʹ������ʱ������Ҫ����ͷ�ļ�
#include <algorithm>		//��׼�㷨��ͷ�ļ�
#include <cassert>
#include <cstdlib>
using namespace std;
/*vector
1. vector�Ǳ�ʾ�ɱ��С�������������
2. ��������һ����vectorҲ���õ������洢�ռ����洢Ԫ�ء�Ҳ������ζ�ſ��Բ����±��vector��Ԫ�ؽ��з��ʣ�������һ����Ч
�����ֲ������飬���Ĵ�С�ǿ��Զ�̬�ı�ģ��������Ĵ�С�ᱻ�����Զ�����
3. ���ʽ���vectorʹ�ö�̬�����������洢����Ԫ�ء�����Ԫ�ز���ʱ�����������Ҫ�����·����СΪ�����Ӵ洢�ռ�
�������ǣ�����һ���µ����飬Ȼ��ȫ��Ԫ���Ƶ�������顣��ʱ����ԣ�����һ����Դ��۸ߵ�����
��Ϊÿ��һ���µ�Ԫ�ؼ��뵽������ʱ��vector������ÿ�ζ����·����С��
4. vector����ռ���ԣ�vector�����һЩ����Ŀռ�����Ӧ���ܵ���������Ϊ�洢�ռ��ʵ����Ҫ�Ĵ洢�ռ����
��ͬ�Ŀ���ò�ͬ�Ĳ���Ȩ��ռ��ʹ�ú����·��䡣����������Σ����·��䶼Ӧ���Ƕ��������ļ����С��
��������ĩβ����һ��Ԫ�ص�ʱ�����ڳ���ʱ��ĸ��Ӷ���ɵġ�
5. ��ˣ�vectorռ���˸���Ĵ洢�ռ䣬Ϊ�˻�ù���洢�ռ��������������һ����Ч�ķ�ʽ��̬����
6. ��������̬�����������(deques, lists and forward_lists)�� vector�ڷ���Ԫ�ص�ʱ����Ӹ�Ч��
��ĩβ��Ӻ�ɾ��Ԫ����Ը�Ч��������������ĩβ��ɾ���Ͳ��������Ч�ʸ��͡�����list��forward_listsͳһ�ĵ����������ø��� */


//vector�ĳ��ú����ӿ�
void test()
{
	//���캯��
	//vector()
	vector<int> vtr1;
	cout << vtr1.capacity() << vtr1.size();		//�������0��˵������û���κ�����

	//vector(size_t n, const T& val = T())
	vector<int> vtr2(10);
	cout << vtr2.size();		//10�������ʼ������Ϊval

	vector<vector<int>> arr(10, vector<int>(10, 5));	//�൱�ڶ�ά����

	//vector(const vector& vtr)
	vector<int> vtr3 = vtr1;

	//������ʼ��
	vector<int> arr1 = { 1,2,3,4 };
	

	//������
	vector<int>::iterator it = vtr1.begin();			//��ͨ������
	vector<int>::const_iterator c_it = vtr1.cbegin();	//�����������������޸ģ�ֻ���Է���
	vector<int>::reverse_iterator r_it = vtr1.rbegin();	//�����������rbegin()�����������һ��λ�����ݵ�ָ��
	//rend()���ص�һ����ǰһ��λ��ָ��

	//size()��capacity
	vtr1.push_back(1);
	cout << vtr1.size() << endl << vtr1.capacity();	

	//empty():�ж��Ƿ�Ϊ�գ��Ǿͷ���true
	vtr1.empty();		//false

	//resize(size_t n, const T& val = T()):�ı������е����ݸ���(size)�����size<n������val��ʼ��

	//reserve():�ı�������capacity
	vtr1.reserve(20);
	cout << vtr1.capacity();		//20
	//ע�⣺reserve()���������ݵ�ָ����С��������������ָ����С��revers���Ի���vector���ݵĴ���ȱ������

	//̽��VS��capacity�����ݹ���
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

	//push_back():β��
	vtr1.push_back(10);
	vtr2.push_back(20);

	//pop_back():βɾ
	vtr1.pop_back();

	//find():�㷨��algorithm.h�ṩ��(string�����find��string�Լ���)������vector��Ա�Ľӿڣ�ʹ��ʱ������������
	vector<int>::iterator f_it = find(vtr1.begin(), vtr1.end(), 2);

	//insert():��ָ��λ��(������)ǰ��������val��vectorû��ͷ��ͷɾ(Ч��̫��)������ʹ��insert����(����)
	vtr1.insert(vtr1.begin(), 1);
	//ע���һ�������ǵ����������Ҳ����λ����ָ��λ�õ�ǰ�棬ʹ�����Ԫ�ص�λ�ñ��ָ��λ��

	//assign():ɾ��ԭ�ռ�����ݣ�Ȼ��ֵ
	vtr2.assign(vtr1.begin(), vtr1.end());
	//assign(int n, T elem)
	vtr2.assign(10, 100);

	//erase()
	vtr1.erase(vtr1.begin());		//ɾ��begin()λ�õ�����
	vtr1.erase(vtr1.begin(), vtr1.end());			//ɾ��������begin()��end()���������

	//swap():������������������(�ײ�ԭ���ǽ���ָ��)
	vtr1.swap(vtr2);		//vtr1��vtr2��������

	//swap��ʵ��Ӧ�ã������ռ�
	vector<int> v2;
	for (int i = 0; i < 100000; i++)
	{
		v2.push_back(i);
	}
	v2.resize(3);		//��ʱsize���3����������ȴ����100000
	vector<int>(v2).swap(v2);
	//�൱�ڿ������촴����һ����������Ȼ���������������v2������������ʱcapacity���С(ϸ��vector��ģ��ʵ��)

	//at():����vector�е�Ԫ��(���ص�������)
	cout << vtr1.at(1);

	//front():��ȡ������һ��Ԫ��
	int front = vtr1.front();

	//back():��ȡ�������һ��Ԫ��(���ص�������)
	int back = vtr1.back();

	//clear():ɾ�������е�����Ԫ��
	v2.clear();
	
	//operator[]:���������е�Ԫ��
	int a = vtr1[1];


	//vector�����ı���
	//��һ��
	for (vector<int>::iterator it = vtr1.begin(); it != vtr1.end(); it++)
	{
		cout << *it << " ";
	}
	
	//�ڶ��֣���Χforѭ��
	for (auto i : vtr1)
	{
		cout << i;
	}


	//��ά�������
	for (vector<vector<int>>::iterator it = arr.begin(); arr.end() != it; ++it)
	{
		for (vector<int>::iterator vit = (*it).begin(); vit != (*it).end(); ++vit)
		//vector<int>::iterator�����ﲻ��ʹ��(*it)::iterator����Ϊvector<int>��ָ�����ͣ���(*it)��������(ϸ��vectorģ��ʵ��)
		{
			cout << *vit << " ";
		}
		cout << endl;
	}
}


//vector������ʧЧ����
void test1()
{
	/*����������Ҫ���þ������㷨�ܹ����ù��ĵײ����ݽṹ����ײ�ʵ�ʾ���һ��ָ�룬�����Ƕ�ָ������˷�װ
	���磺vector�ĵ���������ԭ��ָ̬��T*����˵�����ʧЧ��ʵ�ʾ��ǵ������ײ��Ӧָ����ָ��Ŀռ䱻������
	��ʹ��һ���Ѿ����ͷŵĿռ䣬��ɵĺ���ǳ������(���������ʹ���Ѿ�ʧЧ�ĵ�������������ܻ����)*/

	//1.��Ϊ���ݵ��µ�����ʧЧ
	/*ʹ��resize()��reserve()��insert()��push_back()��assign()�Ȳ���ʱ�������������ռ�ĸı䣬����Ҫ����ʱ
	������ݷ�ʽ���������(�ο�c�����е�calloc����),��ôԭ���ĵ�������ָ��ɿռ�(������ݺ��������)*/
	//����
	vector<int> vtr;
	for (int i = 0; i < 6; i++)
	{
		vtr.push_back(i);
	}
	vector<int>::iterator it = find(vtr.begin(), vtr.end(), 2);
	cout << "����ǰ��*it = " << *it << endl;		//2
	vtr.insert(it, 6);
	cout << "�����*it = " << *it << endl;		//�������
	//��Ϊ��ʱ������������ݣ�ԭ�ڴ汻�ͷţ����������itָ����Ұָ�룬ָ������������
	//ע�⣺���û�з������ݣ���ô����*itָ���ֵӦ����insert��valֵ(ϸ��vect�ű��Ұָ���orģ��ʵ���е�insert)
	//������insert֮��it�ű��Ұָ���

	/*���ʣ�����it���βΣ����Բ���ı�it�����ֵ(insert�����ڲ�������Ҫ������ݺ��ı�posֵ)��������Ǵ��������ǲ��ǿ��Ա������⣿
	�𰸣��ǵģ����ǻ�����µ����⣬�������ǲ����鴫���ã���insert����ײ�ʵ��Ҳ�����	*/

	//�����ʽ����it���¸�ֵ����
	it = vtr.insert(it, 6);			//��ʱit��ֵ����insert�������ص�posֵ(�µĵ�ַ)
	//������Բο�vector��ģ��ʵ��


	//2.��Ϊɾ������(erase)���µ�����ʧЧ
	//iterator erase(iterator pos):ɾ��posλ�õ�Ԫ�أ�����Ҫɾ��λ�õĵ���������һ��������
	vector<int> vtr1;
	for (int i = 0; i < 5; i++)
	{
		vtr1.push_back(i);
	}
	vector<int>::iterator it1 = find(vtr1.begin(), vtr1.end(), 3);
	vtr1.erase(it1);
	cout << *it1;		//�������
	/*�������ÿ��erase��ʹ�øõ���������ʹ��VS�������ֱ�ӱ����ˣ�����ʹ���������������ܲ������
	ʵ��������erase��*it1��ֵΪ4 
	
	eraseɾ��posλ��Ԫ�غ�posλ��֮���Ԫ�ػ���ǰ���ƣ�û�е��µײ�ռ�ĸı䣬�����Ͻ���������Ӧ�û�ʧЧ��
	���ǣ����pos�պ������һ��Ԫ�أ�ɾ��֮��pos�պ���_finish��λ�ã���_finishλ����û��Ԫ�صģ���ôpos��ʧЧ��
	���ɾ��vector������λ����Ԫ��ʱ��vs����Ϊ��λ�õ�����ʧЧ�� */
	
	//���������ʹ��ǰ�Ըõ��������¸�ֵ
}


//����vector����push_back���ι���
class A
{
public:
	A()
	{
		cout << "���캯��";
	}
	~A()
	{
		cout << "��������";
	}
};

void test()
{
	A a;
	vector<A> vtr;
	vtr.push_back(a);
	vtr.push_back(a);
	//���н����һ����ӡ�ı鹹�캯������������
	/*ԭ��
	��һ�Σ���������a
	�ڶ��Σ�push_back���ã����ÿ������캯����������a
	�����Σ�vector������ݣ����ݵ�ַ�����仯�����Ե�һ��Ԫ�ر�ת�ƣ���ʱת�Ʒ�����һ�ι��캯��
	���ĴΣ��ڶ���push_back
	
	����:push_back���Ǵ���������Ϊʲô���ǻ���ù��캯����
	��Ϊpush_back�ײ���õ���insert����insert������ֵ����	*/

	vector<A> vtr1;
	vtr1.resize(2);
	vtr1.push_back(a);
	vtr1.push_back(a);		//��ʱ��ֻ��������
}


//ģ��ʵ��vector����
#include <string>
#include <iostream>
#include "vector.h"
using namespace std;
int main()
{
	yw::vector<string> vtr1;
	vtr1.push_back("����");
	vtr1.insert(vtr1.begin(), "����");
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


