#include <iostream>
#include <cassert>
using namespace std;

//listģ��ʵ��
namespace yw
{
	//����ڵ�
	template<class T>
	struct ListNode
	{
	public:
		ListNode<T>* _prev;
		ListNode<T>* _next;
		T _data;
		ListNode(const T& data = T()) :_prev(nullptr), _next(nullptr), _data(data)
		{}
	};


	//��װһ�������������ǽ�����������һ������
	//Ȼ�����װ�ɺ�ָ��һ�������ã����ع��ڶ�ָ���һЩ���õ����������(==��!=��*��->��++��--)
	template<class T, class Ref, class Ptr>		//���������ֱ����T���ͣ�T�������ã�T����ָ��(��list���е�������Ӧ)
	struct _list_iterator
	{
		typedef ListNode<T> Node;
		typedef _list_iterator<T, Ref, Ptr> self;	//����������

		typedef Ref reference;
		typedef Ptr pointer;

		Node* _node;		//����ڵ�ָ�����

		//���캯��
		_list_iterator(Node* node) :_node(node) {};
		//����������Ҫ�Լ�д�����������������캯������ֵ����
		//ʹ��Ĭ�����ɵľͿ��ԣ���Ϊ����������Ҫ�ͷŽڵ�(���Բ����ڶ����ڴ����ͷ�����)
		//����������������ô���൱�����´�����һ��������������

		Ref operator*()		//Ref�������ʾ�������ã����list��������T&ʵ��������T&�������const T&ʵ��������const T&
		{
			return _node->_data;
		}

		Ptr operator->()	//һ�������Զ����������ͣ�����ֱ�ӷ��ʳ�Ա����
		{
			return &_node->data;
		}
		/*ΪʲôҪ������������T,Ref,Ptr�ֱ����ֵ�����ú�ָ�룬����ֱ��ʹ��һ������T��
		��Ϊ���Ƿ��֣������ǶԵ�����ʹ��ʱ��������ʱ����Ҫ����ֵ����ʱ����Ҫ������ָ�������
		�Ӷ����ڲ���Ա�����޸ģ��������ֻ��T��һ��ģ���������ô�������оͻ���ںܶ�Ĳ���Ҫ�Ŀ����Ȳ���
		��������ʵ�ֶ��ģ���������������ֵ�Ϳ����и��������ѡ�����������ǵ�Ҫ��	*/


		//ǰ��++(��Ҫ�������ã���Ϊ����++��Ȼ����ʹ�ñ���)
		self& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		//����++
		self operator++(int)
		{
			self tmp(*this);
			_node = _node->_next;
			return tmp;
		}
		//����++���ܷ��ر���(�����÷���)����Ϊ����++��Ҫ��ʹ����++������ֻ�ܷ���tmp�����Ǳ����λ���Ѿ��ı�
		//tmp����ʱ�������Բ��ܴ����÷���
		//��ǰ��++�ͺ���++�����������£�������ǰ��++����Ϊ����Ҫ��������

		//ǰ��--
		self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		//����--
		self operator--(int)
		{
			self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}

		bool operator!=(const self& it)
		{
			return this->_node != it._node;
		}

		bool operator==(const self& it)
		{
			return _node == it._node;
		}
	};

	//��������Iterator���ĸ������ĵ�������reverse_iterator<Iterator>�Ϳ���������䷴�������
	template<class Iterator>
	class reverse_iterator
	{
	private:
		typedef reverse_iterator<Iterator> self;
		Iterator _it;		//�����Iterator����_list_iterator��ֻ�ǻ�û��ʵ����
	public:
		reverse_iterator(Iterator it) :_it(it) {};
		//���ﴫ��ĵ�����it�ͻ��ɷ��������_it

		//��ʱ��Iterator��û��ʵ��������֪�������_list_iterator�����Բ���ֱ��ʹ��::��Ҫ����typename��ǰ��֪���������
		typename Iterator::reference operator*()
		{
			Iterator prev = _it;		//��ֹ_it���޸�
			return *(--prev);		//�����������beginָ��ͷ��㣬���Է����������Ҫ--�����ʹ��
			//�����*��_list_iterator�����ص�*
		}

		typename Iterator::pointer operator->()
		{
			return &operator*();
		}

		self& operator++()
		{
			--_it;			//ע�ⷴ���������++���������������--
			return *this;
		}

		self operator++(int)
		{
			self tmp(_it);
			--_it;
			return tmp;
		}

		self& operator--()
		{
			++_it;
			return *this;
		}

		self operator--(int)
		{
			self tmp(_it);
			++_it;
			return tmp;
		}

		bool operator==(const self& r_it)
		{
			return _it == r_it._it;
		}

		bool operator!=(const self& r_it)
		{
			return _it != r_it._it;
		}
	};

	template<class T>
	class list
	{
		typedef ListNode<T> Node;
	public:
		typedef _list_iterator<T, T&, T*> iterator;		//����������
		typedef _list_iterator<T, const T&, const T*> const_iterator;

		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		iterator begin()
		{
			return iterator(_head->_next);		//���ù��캯��������������
		}

		iterator end()
		{
			return iterator(_head);
		}

		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}

		const_iterator end() const
		{
			return const_iterator(_head);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(_head);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(_head->_next);
		}

		//���캯��
		list()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			//data���ܣ���Ϊͷ�ڵ㲻��Ҫ�������
		}

		list(size_t n, const T& val = T())
		{
			_head = new Node();		//�Ӳ������Ŷ�����
			_head->_next = _head;
			_head->_prev = _head;
			for (size_t i = 0; i < n; i++)
			{
				push_back(val);		//���ݽ���push_back
			}
		}

		list(int n, const T& val = T())
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			for (int i = 0; i < n; i++)
			{
				push_back(val);
			}
		}
		//���������ĺ������ɺ������أ�����ʵ����Ϊ�˽��һ��bug
		/*���û��д����������أ���ôlist(int, int)���ú�����ѡ�����InputIterator��
		���캯������ΪInputIterator(ģ�����)��list(size_t, list)����ƥ�䣬��ô��ʱ�ͻ���ڴ���	*/

		template<class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			for (InputIterator it = first; it != last; it++)
			{
				push_back(*it);
			}
		}

		list(const list<T>& st)
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			list<T> tmp(st.begin(), st.end());	//���캯���ĸ���
			std::swap(_head, tmp._head);		//����ͷ��㼴��
			//��ʱ����tmp���ں����������ڽ���ʱ�Զ�������������������Դ
		}

		/*��ͳд��
		list(const list<T>& st)
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			for (auto e : st)
			{
				push_back(e);
			}
		}*/

		list<T>& operator=(list<T> st)		//����ʱ���ÿ�������
		{
			/*��¼�����������ڵ���ʱ������һ��bug
			����һ��ʼ���δ�����const list<T> st����ʱ���ǵ���swap�����ᱨ��������Ϊ���ǲ���Ϊconst����
			ʹ��swap�൱�ڽ�const��������������޸��ˣ����Ծͱ����� */
			std::swap(this->_head, st._head);
			return *this;
		}

		/*��ͳд��
		list& operator=(const list<T> st)
		{
			if (this != &st)	//�������������
			{
				clear();
				for (auto e : st)
				{
					push_back(e);
				}
			}
			return *this;
		}	*/

		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}

		void clear()
		{
			/*iterator it = begin();
			while (it != end())
			{
				erase(it++);		//���ﲻ�ֿܷ�д(������ʧЧ����)
			}*/

			iterator it = begin();
			while (it != end())
			{
				iterator del = it++;
				delete del._node;		//_node����list����new�����ģ�����ɾ�������˵���������ĳ�Ա_node�����ǻ�����list����ɾ����
			}
			_head->_next = _head;
			_head->_prev = _head;
		}

		bool empty()
		{
			return _head->_next == _head;
		}

		void push_front(const T& val)
		{
			insert(begin(), val);
		}

		void pop_front()
		{
			assert(!empty());
			erase(begin());
		}

		void push_back(const T& val)
		{
			insert(end(), val);
		}

		void pop_back()
		{
			assert(!empty());
			erase(--end());
		}

		iterator insert(iterator pos, const T& val)
		{
			Node* newNode = new Node(val);
			newNode->_next = pos._node;
			newNode->_prev = pos._node->_prev;
			pos._node->_prev->_next = newNode;
			pos._node->_prev = newNode;
			return iterator(newNode);		//���ù��캯�������������󣬷��ز���Ԫ�صĵ�����
		}

		iterator erase(iterator pos)		//ɾ����pos��������ʧЧ��
		{
			assert(pos != end());
			pos._node->_prev->_next = pos._node->_next;
			pos._node->_next->_prev = pos._node->_prev;
			Node* next = pos._node->_next;
			delete pos._node;
			return iterator(next);
		}
	private:
		Node* _head;		//ͷ���
	};
}

