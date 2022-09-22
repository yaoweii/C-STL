#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <deque>
using namespace std;

/*stack
1. stack��һ��������������ר�����ھ��к���ȳ������������Ļ����У���ɾ��ֻ�ܴ�������һ�˽���Ԫ�صĲ�������ȡ����
2. stack����Ϊ������������ʵ�ֵģ��������������Ƕ��ض����װ��Ϊ��ײ�����������ṩһ���ض��ĳ�Ա������������Ԫ��
���ض�����Ϊ��ײ㣬Ԫ���ض�������β��(��ջ��)��ѹ��͵���
3. stack�ĵײ������������κα�׼��������ģ�����һЩ�����ض��������࣬��Щ������Ӧ��֧�����²�����
empty���пղ���						back����ȡβ��Ԫ�ز���
push_back��β������Ԫ�ز���			pop_back��β��ɾ��Ԫ�ز���
4. ��׼����vector��deque��list��������Щ����Ĭ������£����û��Ϊstackָ���ض��ĵײ�������Ĭ�������ʹ��deque */


//stack�ĺ����ӿ�
void test()
{
	//���캯��
	//stack(const container_type& con = container_type())
	//�����container_type������������Ĭ��Ϊdeque
	stack<int> sk1;

	stack<int, vector<int>> sk3;		//ָ���ײ�����Ϊvector

	stack<int> sk2(sk1);

	//operator=(const stack<T>& sk)
	sk2 = sk1;

	//push(T val):ѹջ
	sk1.push(10);

	//pop():��ջ
	sk1.pop();

	//top():����ջ��Ԫ��
	int ret = sk1.top();

	//empty():�ж�ջ�Ƿ�Ϊ��
	sk1.empty();

	//size():����ջ�д���Ԫ�ظ���
	sk1.size();

	//swap():��������ջ������
	sk1.swap(sk2);
}


/*queue
1. ������һ��������������ר��������FIFO������(�Ƚ��ȳ�)�в��������д�����һ�˲���Ԫ�أ���һ����ȡԪ��(β�壬ͷɾ)
2. ������Ϊ����������ʵ�֣����������������ض��������װ��Ϊ��ײ������࣬queue�ṩһ���ض��ĳ�Ա������������Ԫ��
Ԫ�شӶ�β����У��Ӷ�ͷ������
3. �ײ����������Ǳ�׼������ģ��֮һ��Ҳ����������ר����Ƶ������ࡣ�õײ�����Ӧ����֧�����²���:
empty���������Ƿ�Ϊ��			size�����ض�������ЧԪ�صĸ���
front�����ض�ͷԪ�ص�����		back�����ض�βԪ�ص�����
push_back���ڶ���β�������		pop_front���ڶ���ͷ��������
4. ��׼������deque��list��������ЩҪ��Ĭ������£����û��Ϊqueueʵ����ָ�������࣬��ʹ�ñ�׼����deque	*/

//queue���ýӿ�
void test()
{
	//���캯��
	//queue(const container_type& con = container_type())
	queue<int> qu1;
	queue<int, list<int>> qu2;

	//queue(const queue<T>& qu)
	queue<int> qu3(qu1);

	//queue<T>& operator=(const queue<T>& que)
	qu1 = qu3;

	//push():���
	qu1.push(10);

	//pop():���ӣ�����ͷ��Ԫ�ؽ���ɾ����ͷ������
	//ע�⣺��Ϊqueue�ĵײ���list��deque��������ײ�ʵ������һ��ͷ���ģ�ֻ��queue�����װ��
	qu1.pop();

	//front():���ض�ͷԪ�ص�����(ע��������ﲻ��const�ǿ����޸Ķ����е�Ԫ�����ݵ�)
	int ret = qu1.front();

	//back():���ض�βԪ�ص�����(���������һ����ͬ�������޸�ret���޸Ķ����е�Ԫ������)
	ret = qu1.back();

	//empty()���ж��Ƿ�Ϊ��
	qu1.empty();

	//size()�����ض���Ԫ�ظ���
	qu1.size();

	//swap():���������е�����(���ʾ��ǽ���ͷ���)
	qu1.swap(qu3);
}

//�ܽ᣺�����е�back()��front()��at()�������صĶ�������


//stack��queueģ��ʵ�ֵĲ���
#include "stack-queue.h"
int main()
{
	yw::stack<string, vector<string>> sk;
	sk.push("����");
	sk.push("����");
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