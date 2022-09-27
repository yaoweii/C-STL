#include <iostream>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

/*����ʽ�����͹���ʽ����
����ʽ������vector��list��deque�ȡ��ײ�Ϊ�������е����ݽṹ�����д��Ԫ�ر���

����ʽ��������ŵ���pair<key,value>�ṹ�ļ�ֵ�ԣ�����Ӧ�ó����Ĳ�Ͱ��STL�ܹ�ʵ�������ֲ�ͬ�ṹ�Ĺ���ʽ���������ͽṹ���ϣ�ṹ
���ͽṹ�Ĺ���ʽ������Ҫ�����֣�map��set��multimap��multiset
�����������Ĺ�ͬ���ǣ���ײ�ʵ��ʹ��ƽ��������(�����)�������е�Ԫ����һ�����������

��ϣ�ṹ�Ĺ���ʽ�����У�unordered_set��unordered_map��unordered_multiset��unordered_multimap
�����������Ĺ�ͬ���ǣ���ײ�ʵ��ʹ�ù�ϣ�����������е�Ԫ������	*/


//set��������

//set����ģ�����
/*template<class T, class Compare = less<T>, class Alloc = allocator<T>>
T:set��ŵ�Ԫ�����ͣ�ʵ���ڵײ�洢pair<T, T>��ֵ�ԣ���key��valueһ��
Compare<T>:�º�����set���Ԫ�ص�˳��Ĭ�ϰ���С�����Ƚϣ����Ϊ����(����������Ϊ����)
Alloc:�ռ��������������������ж�����������һ���������ӿ��������ڴ��Ч��	*/

//set��ÿ��value����Ψһ�ģ�����set�е�Ԫ�ز����޸�(Ԫ������const)�����ǿ��Բ����ɾ��
//set����ͨ��key���ʵ���Ԫ�ص��ٶ�ͨ����unordered_set���������������������˳����Ӽ�����ֱ�ӵ���
//�����ݷ���set���������ֶΰ������������+ȥ�صĹ���

void test()
{
	//���캯��
	//set(const Compare& cmp = Compare())
	//set<int> s1(std::less<int>());	//error����Ȼ����ģ������ȷʵ��Compare������͵Ĳ���������set����ģ������Ҳ����Compare
	//���Һ���ģ�������Compare��������set�����ģ�����set������ģ���Ѿ���Ĭ�ϵĲ�������less<int>�����Բ����ں���ģ����������ָ��
	//��Ҳ˵����list�����е��Ǹ�����(��������е���������������Ĳ���������ȱʡֵһ��)

	//��ȷд��
	set<int, std::less<int>> s1;
	set<int> s2;

	//set(InputIterator first, InputIterator last, const Compare& cmp = Compare())
	set<int> s3(s2.begin(), s2.end());

	//set(const set<T>& s)
	set<int> s4(s3);

	//����
	set<int> s5 = { 1,2,3,4,5 };

	//set�ĵ�����
	//iterator begin():����������ʼλ��Ԫ�ص�����
	set<int>::iterator it = s1.begin();

	//iterator end():�������������һ��Ԫ�غ���ĵ�����
	
	//const_iterator cbegin() const:������������ʼλ��Ԫ�ص�const������
	set<int>::const_iterator c_it = s1.cbegin();

	//const_iterator cend() const:�������������һ��Ԫ�غ����const������

	//reverse_iterator rbegin():�������һ��Ԫ�صķ��������
	set<int>::reverse_iterator r_it = s1.rbegin();

	//reverse_end() rend():����������һ��Ԫ�ص�ǰһ��λ�õĵ�����

	//const_reverse_iterator crbegin() const:�������������һ��Ԫ�صķ���const������
	set<int>::const_reverse_iterator cr_it = s1.crbegin();

	//const_reverse_iterator crend() const:���������е�һ��Ԫ�ص�ǰһ��λ�õķ��������


	//empty()
	cout << set<int>().empty();		//1

	//size():����set����ЧԪ�ظ���
	s1.size();

	//pair<iterator, bool> insert(const T& val):�������в���valֵ(ʵ���ǲ���<val, val>��ֵ��)
	//����ɹ�����<��Ԫ����������λ��(������), true>������ʧ�ܣ�˵��val�Ѿ����ڣ�����<val�������еĵ�����, false>
	pair<set<int>::iterator, bool> p1 = s1.insert(10);
	//set��������û��push������ֻ��insert����

	//void erase(iterator pos):ɾ��������posλ���ϵ�Ԫ�أ�pos���������������
	//���pos��ͨ��find�ҵ��ģ���ô��ɾ��ǰ���һ���Ƿ�==set::end�����pos������Чλ�ã�ɾ���ᱨ��
	s1.erase(s1.begin());

	//size_t erase(const T& val):ɾ��������ֵΪval��Ԫ�أ�����ɾ����Ԫ�ظ��������val�����ڲ��ᱨ��(������ֵֻ��0��1)
	size_t count = s1.erase(10);

	//void erase(iterator first, iterator last):ɾ��[first, last)�����Ԫ��

	//void swap(set<T>& s):������������

	//void clear():�������

	//size_t count(const T& val) const:����������ֵΪval��Ԫ�ظ���

	//iterator find(const T& val) const:����set��valԪ�صĵ��������Ҳ�������set::end()
	set<int>::iterator f_it = s1.find(10);
}

//set���������find���㷨�������find�죬��������:
void test()
{
	srand((size_t)time(nullptr));
	set<int> s;
	for (size_t i = 0; i < 10000; i++)
	{
		s.insert(rand());
	}
	cout << "����Ԫ�ظ���:" << s.size() << endl;
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
	cout << "������find()������ʱ:" << end1 - begin1 << endl;
	cout << "�㷨���find()������ʱ:" << end2 - end1;
}



//multiset
//multiset��������ظ�ֵ�������set��ʹ����ͬ

//�����ظ�ֵ�Ĵ���:����һ���ظ����ֵ�ֵ��multiset���ص�һ������multiset������ֵ�ĵ�����
//ʹ��erase����ʱ��ɾ�������ظ�ֵ
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
//����ģ�����
//template<class key, class value, class Compare& = less<key>>

/*mapʹ�ù���ʽ������ÿ��Ԫ��Ϊ��ֵ��ӳ��ֵ����ϣ�Ԫ��֮������ض��Ĵ���
map��keyֵ���������Լ�Ψһ��ʶԪ�أ�value�д洢���ֵkey���������ݡ���ֵkey��ֵvalue�����Ϳ��ܲ�ͬ
map�е�valueֵ�������ظ�������keyֵΨһ�����ڲ���map�е�Ԫ�����ǰ��ռ�ֵkey���бȽ������(����ķ�ʽ���Ƿº���less��greater)
map��ͨ����ֵ���ʵ���Ԫ�ص��ٶ�ͨ����unordered_map����������map�������˳���Ԫ�ؽ���ֱ�ӵ���(����map�е�Ԫ�ؽ��е���ʱ�����Եõ�һ�����������)
map֧���±���ʷ�������[]�з���key���Ϳ����ҵ���key��Ӧ��value��keyֵ��map����Ψһ��	*/

//map�����ӿ�
void test()
{
	//���캯��
	//map(const Compare& = Compare())
	map<int, string> m1;
	map<int, string, greater<int>> m11;

	//map(InputIterator first, InputIterator last, const Compare& cmp = Compare())
	map<int, string> m2(m1.begin(), m1.end());

	//map(const map& m)
	map<int, string> m3(m2);

	//map�ĵ�������set���ƣ�����ע��:�õ�����������Ҫ�ü�ͷ����ȡpair��first(��ֵ)��value(ʵֵ)
	map<int, string>::iterator it = m1.begin();
	cout << it->first << " " << it->second << endl;

	//size():����������ЧԪ�ظ���

	//empty():�ж������Ƿ�Ϊ��

	//pair<iterator, bool> insert(const pair<key, value>& p)
	m3.insert(pair<int, string>(1, "Tom"));		//������������
	m3.insert(make_pair(2, "Jerry"));			//ʹ��make_pair����(����)
	//����ɹ������ز���Ԫ�صĵ�������true������ʧ��˵��Ԫ���Ѿ���map�д��ڣ�����map�м�ֵΪkey�ĵ�������false

	//iterator find(const key& k):����keyֵ�Ϳ��Բ��ң�û���ҵ�����map::end()

	//size_t count(const key& k) const:ֻ������keyֵ�Ϳ��Եõ�key�������ĸ���

	//size_t erase(const key& k):ɾ��ָ����keyֵ��Ԫ�أ�ɾ�����ɹ����ᱨ������ɾ��Ԫ�ظ���

	//void erase(iterator pos):ɾ��ָ��������λ�����ڵ�Ԫ�أ�ɾ�����ɹ��ᱨ��

	//swap():��������map����
}

//map��[]��������(�ص�)
//value& operator[](const key& k):�亯����������keyֵ
//[]���غ����ķ���ֵΪ:(*((this->insert(make_pair(k, value()))).first).second
/*�����������:
1. ����insert���������ֵ��
2. �ó���insert������ȡ���ĵ�����
3. ���ظõ�����λ��Ԫ�ص�ֵvalue	*/

//�����������
template<class key, class value>
value& operator[](const key& k)
{
	pair<iterator, bool> ret = this->insert(make_pair(k, value()));		//ͨ��insert�����ҵ�k�ĵ�������ַ
	iterator it = ret.first;		//��ȡk�ĵ�����
	return it.second;			//����valueֵ
}

//����������
void test()
{
	map<int, string> m;
	m.insert(make_pair(1, "one"));
	m.insert(make_pair(2, "two"));
	m.insert(make_pair(3, "three"));

	m[2] = "Tom";		//�޸�keyֵΪ2��Ԫ�ص�valueֵ

	m[6] = "six";		//�����ֵ��(6, "six")
	//����ķ��ؽ���ǲ����ֵ��(6, "six")���value������

	for (auto e : m)
	{
		cout << e.first << "->" << e.second << endl;
	}
}


//multimap
//multimap��map�������multiset��set������һ����multimap������ظ�
//multimap��map�ĺ����ӿڻ���һ�£�����ֻ����һЩ�в���ĳ�Ա����
void test()
{
	//find(const key& k):���ص�һ������ļ�ֵΪkey��Ԫ�ص�����
	multimap<int, string> mmp;
	mmp.insert(make_pair(1, "one"));
	mmp.insert(make_pair(2, "two"));
	mmp.insert(make_pair(1, "Tom"));

	map<int, string>::iterator it = mmp.find(1);
	cout << it->second;		//one

	//size_t count(const key& k):���ؼ�ֵΪk��Ԫ�ظ���

	//ע�⣺����multimap���������ֵ���࣬����[]��������غ���ʱ������ֵ�������壬����multimapû��ʵ��[]���������
}


//map��setģ��ʵ�ֵĲ���
#include "map-set.h"
int main()
{
	yw::set<string> s;
	s.insert("����");
	s.insert("����");
	s.insert("����");
	yw::set<string>::iterator s_it = s.find("����");
	cout << *s_it << endl;
	s.erase("����");
	for (auto e : s)
	{
		cout << e << endl;
	}

	yw::map<string, int> m;
	m.insert(make_pair("����", 1));
	m.insert(make_pair("����", 2));
	m.insert(make_pair("����", 3));
	yw::map<string, int>::iterator ret = m.find("����");
	cout << ret->second << endl;
	m.erase("����");
	m["����"] = 1;
	for (auto e : m)
	{
		cout << e.first << ":" << e.second << endl;
	}
	return 0;
}
