#include <map>
#include <iostream>
using namespace std;

//����pair
/*pair�ǽ�2��������ϳ�һ�����ݣ���stl�е�map���ǽ�key��value����һ�������棬���ߵ�һ��������Ҫ����2�����ݵ�ʱ��Ҳ����ѡ��pair
pair��ʵ����һ���ṹ�壬��Ҫ��������Ա����first��second���ֱ�洢��������	*/

void test()
{
	//pair��������ʼ����ʽ
	pair<int, string> p1(1, "Tom");
	pair<int, string> p2 = make_pair(2, "Jerry");		//ע��:�����Ǻ���ʹ��make_pair��Ϊ����ֵ���߲���ʱ������Ϊ���ã���make_pair��Ϊ��������ʱ����Ҫ��const����
	pair<int, string> p3;
	p3.first = 3;
	p3.second = "Beken";

	//pair<int, string> p4 = (4, "Jhon");		//error
}

//pairģ��ʵ��
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

	//make_pair����ʵ��
	template<typename T1, typename T2>
	pair<T1, T2> make_pair(T1& x, T2& y)
	{
		return yw::pair<T1, T2>(x, y);		//������������
	}
}

void test()
{
	yw::pair<int, string> p1(1, "tom");
	yw::pair<int, string> p2 = p1;
	p2.first = 2;
}