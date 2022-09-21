#include <iostream>
#include <string>
#include <forward_list>
using namespace std;

/*forward_list��������һ�������������к�list������ͬ�����ԣ����ó������е��κ�λ�ý��в���Ԫ�ػ�ɾ��Ԫ�صĲ���
���⣬���ڵ�����û��˫������������������list������forward_list�����Ĺ����ܵ��˺ܶ�����
���磬���ڵ�����ֻ�ܴ�ǰ������������֧�ַ����������� forward_list ����ֻ�ṩǰ���������������˫�������
����ζ�ţ�forward_list����������rbegin()��rend()֮��ĳ�Ա����

forward_list�ŵ�:�洢��ͬ������ͬ����Ԫ�أ���������õ��ڴ�ռ���٣��ռ������ʸ��ߣ����Ҷ���ʵ��ĳЩ�����������ִ��Ч��Ҳ����
Ч�ʸ���ѡ��forward_list������list��������Ҫ��ԭ�򣬻��仰˵,ֻҪ��list������forward_list��������ʵ�ֵĲ�����Ӧ����ѡ��forward_list����	*/

//forward_list�ĳ��ú����ӿ�
void test()
{
	//forward_list()
	forward_list<int> fst1;

	//before_begin():�����ڱ�λ�ĵ�����
	forward_list<int>::iterator b_it = fst1.before_begin();

	//begin():���ص�һ��Ԫ�صĵ�����
	//end():�������һ��Ԫ�ص���һ��λ�õĵ�����(�����ڱ�λ�����ǻᴴ��һ��ֵΪ0�ĵ���������)

	//empty():�ж������Ƿ�Ϊ�գ��ǿշ���true

	//T& front():���ص�һ��Ԫ��(�����޸�)
	int val = fst1.front();

	//assign(InputIterator first, InputIterator last)
	//assign(size_t n, T& val = T())
	//assign�����Ḳ��ԭ����������

	//push_front()
	fst1.push_front(10);

	//pop_front()
	fst1.pop_front();

	//clear()

	//resize(size_t n, const T& val = T())
	fst1.resize(10);

	//insert_after(iterator pos, T& val):��pos�������Ԫ��val
	fst1.insert_after(fst1.begin(), 10);

	//erase_after(iterator pos):ɾ��pos���������
	fst1.erase_after(fst1.begin());

	//remove(T& val):ɾ�����������е���val��Ԫ��
	fst1.remove(10);

	//swap(forward_list<T>& fst):��������������Ԫ��(���ǽ���ͷ���)

	//merger(const forward_list<T>& fst):�ϲ���������forward_list���������ұ�֤�ϲ�����Ȼ����

	//sort():����(Ĭ������)

	//reverse():��ת����

	//���Ƿ���forward_listû��size()�����������Ҫ����������size������ʹ��ͷ�ļ��е�distance()����
	forward_list<int> fst2 = { 1,2,3,4,5 };
	cout << distance(fst2.begin(), fst2.end());			//5

	//forward_list������listһ��Ҳ��֧��������ʣ�������ֻ��++����--������ +��- ���ֵ
}