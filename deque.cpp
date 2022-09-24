#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
#include <ctime>
using namespace std;
//deque����һ��˫�����飬���Խ���ͷ���Ĳ����ɾ��
/*deque��vector������
vector����ͷ���Ĳ���ɾ��Ч�ʵͣ�������Խ��Ч��Խ�ͣ�deque��Զ��ԣ���ͷ���Ĳ���ɾ���ٶȻر�vector��

vector����Ԫ��ʱ���ٶȻ��deque��,��������ڲ�ʵ���й�
deque ���ڲ�ʵ��ԭ��
��deque�������ڲ���һ���п����Ķ�����������ÿһС�ε����飬������������ʵ���ݣ����п�����ŵ���ÿһС��������׵�ַ
����Ҫͷ�����ݵ�ʱ���������п�����Ѱ�ң��ҵ�һ�����鿴���Ƿ�ͷ�����Բ������ݣ�������Ծ����ҵ���λ�ò���
û�еĻ����ͻ����¿���һ���ڴ棬ָ�����飬�������ݡ�ɾ��ͷ��Ҳ��һ����ÿһ��С���鶼�������ģ���Ϊ�п����ĵ�ַҲ�������ģ�ʹ��deque��һ�������Ŀռ�
�������ݲ���ô���ԭ������Ϊ����Ҫ���п������ҵ���ַ����ȥ���������Ԫ�أ������е���	

deque���ڲ��ṹ��http://t.csdn.cn/j5LyR	*/


//deque���ú����ӿ�
void test()
{
	//���캯��
	//deque():Ĭ�Ϲ���
	deque<int> dq1;

	//deque(InputIterator first, InputIterator last):��[first, last)�ռ�����ݿ�����deque����
	deque<int> dq2(dq1.begin(), dq1.end());

	//deque(size_t n, T& val = T()):��n��val���ݸ�deque����
	deque<string> dq3(10, "����");

	//deque(const deque<T>& dq):�������캯��
	deque<string> dq4(dq3);

	//����
	deque<int> dq5 = { 1,2,3,4,5 };

	//��ֵ����
	//deque<T>& operator=(const deque<T>& dq)
	dq3 = dq4;

	//assign(InputIterator first, InputIterator last):��[first, last)�����ֵ����������
	dq3.assign(dq4.begin(), dq4.begin() + dq4.size());
	//ע�⣺deque�ĵ�������֧�ּ����ֵ�ģ���ֻ��++��--(����� ������ + ������ ��+Ҳ�����ص�)

	//assign(size_t n, T& val = T()):��n��val���ݿ���������
	dq3.assign(10, "Tom");
	//ע�⣺assign�����Ὣԭ���������������ɾ��

	//empty():�ж��Ƿ�Ϊ�գ��ǿշ���true
	cout << dq3.empty() << endl;			//0

	//size():����deque���������ݸ���
	size_t count = dq3.size();

	//resize(size_t num, cosnt T& val):��size��Ϊnum�����num > szie����ô���ݣ��������ָ�ֵΪval�����С����βɾ��������
	dq3.resize(20);
	//deque����û��capacity���������������

	//push_back(T& val):β��
	dq3.push_back("TiMi");

	//pop_back():βɾ
	dq3.pop_back();

	//push_front():ͷ��
	dq3.push_front("IT");

	//pop_front():ͷɾ
	dq3.pop_front();

	//insert(const_iterator pos, T& val):ָ��������posǰ����val�����ز������ݵ�λ��
	dq2.insert(dq2.begin(), 100);

	//insert(const_iterator pos, size_t n, T& val):ָ��������posǰ����n��val����
	dq2.insert(dq2.begin() + dq2.size(), 2, 100);

	//insert(const_iterator pos, InputIterator first, InputIterator last):��posλ��ǰ����[first, last)�����ֵ
	dq1.insert(dq1.begin(), dq2.begin(), dq2.end());

	//clear()		//�����������
	dq3.clear();

	//erase(iterator begin, iterator end):ɾ��[begin, end)�����Ԫ�أ�������һ�����ݵĵ�����
	dq1.erase(dq1.begin(), dq1.begin() + 1);

	//erase(pos):ɾ��posλ�����ݣ�������һ�����ݵĵ�����
	dq2.erase(dq2.begin());

	//T& operator[](size_t n)
	dq2[2] = 50;

	//T& at(size_t n)
	dq1.at(0) = 50;

	//T& front():����������һ��Ԫ��
	dq1.front();

	//T& back():�����������һ��Ԫ��
	dq2.back();


	//deque����������
	dq1.resize(0);
	for (int i = 10; i >= 0; i--)
	{
		dq1[i] = i;
	}
	//Ĭ���������������
	sort(dq1.begin(), dq1.end());	//��Ҫ�����׼�㷨ͷ�ļ�
	//���ڿ���������ʵĵ�����������������sort�㷨���������������vector

	for (auto e : dq1)
	{
		cout << e << " ";
	}			//0 1 2 3 4 5 6 7 8 9 10
}


//����������ѡ��ABCDE��ʮ����ί��֣�ȥ����߷�ȥ����ͷ�
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
		string name = "ѡ��";
		name += ch[i];
		int score = 0;
		Person p(name, score);
		//��������Person�������������
		v.push_back(p);
	}
}
void SetScore(vector<Person>& v)
{
	for (int i = 0; i < v.size(); ++i)
	{
		//����ί�ķ����ŵ�deque������
		deque<int>Score(10);
		for (int i = 0; i < Score.size(); ++i)
		{
			srand(time(NULL));
			int score = rand() % 41 + 60;		//����һ��60-100�ķ���
			Score.push_back(score);
		}
		sort(Score.begin(), Score.end());
		Score.pop_back();
		Score.pop_front();
		int cout = 0;
		for (int i = 0; i < Score.size(); ++i)		//����ÿ���˵��ܷ�
		{
			cout += Score[i];
		}
		cout = cout / (float)Score.size();		//����ƽ����
		v[i].score = cout;			//��ƽ���ַŵ�ÿ���˵�score��Ա��
	}
}
void PrintScore(vector<Person>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i].name << "�ķ���Ϊ" << v[i].score << endl;
	}
}
int main()
{
	//��������ѡ��
	vector<Person> vtr(5);
	//ѡ�ֳ�ʼ��
	CreatPerson(vtr);
	//���÷���
	SetScore(vtr);
	//��ӡÿ��ѡ�ֵ�ƽ����
	PrintScore(vtr);
	return 0;
}