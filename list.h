#include <iostream>
#include <cassert>
using namespace std;

//list模拟实现
namespace yw
{
	//链表节点
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


	//封装一个迭代器，我们将迭代器看成一个对象
	//然后将其封装成和指针一样的作用，重载关于对指针的一些常用的运算符操作(==、!=、*、->、++、--)
	template<class T, class Ref, class Ptr>		//三个参数分别代表T类型，T类型引用，T类型指针(和list类中的声明对应)
	struct _list_iterator
	{
		typedef ListNode<T> Node;
		typedef _list_iterator<T, Ref, Ptr> self;	//迭代器对象

		typedef Ref reference;
		typedef Ptr pointer;

		Node* _node;		//定义节点指针变量

		//构造函数
		_list_iterator(Node* node) :_node(node) {};
		//迭代器不需要自己写析构函数、拷贝构造函数、赋值重载
		//使用默认生成的就可以，因为迭代器不需要释放节点(所以不存在堆区内存多次释放问题)
		//而且如果是深拷贝，那么就相当于重新创建了一个链表，容易乱套

		Ref operator*()		//Ref在这里表示返回引用，如果list传过来是T&实例化就是T&，如果是const T&实例化就是const T&
		{
			return _node->_data;
		}

		Ptr operator->()	//一般用于自定义数据类型，可以直接访问成员变量
		{
			return &_node->data;
		}
		/*为什么要设置三个参数T,Ref,Ptr分别代表值，引用和指针，而不直接使用一个参数T？
		因为我们发现，在我们对迭代器使用时，我们有时候需要返回值，有时候需要返回其指针或引用
		从而对内部成员进行修改，如果我们只有T这一个模板参数，那么整个类中就会存在很多的不必要的拷贝等操作
		所以我们实现多个模板参数，这样返回值就可以有更多的自主选择来满足我们的要求	*/


		//前置++(需要返回引用，因为其先++，然后再使用本身)
		self& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		//后置++
		self operator++(int)
		{
			self tmp(*this);
			_node = _node->_next;
			return tmp;
		}
		//后置++不能返回本身(即引用返回)，因为后置++需要先使用在++，所以只能返回tmp，但是本身的位置已经改变
		//tmp是临时对象，所以不能传引用返回
		//在前置++和后置++都允许的情况下，建议用前置++，因为不需要拷贝构造

		//前置--
		self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		//后置--
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

	//适配器：Iterator是哪个容器的迭代器，reverse_iterator<Iterator>就可以适配出其反向迭代器
	template<class Iterator>
	class reverse_iterator
	{
	private:
		typedef reverse_iterator<Iterator> self;
		Iterator _it;		//这里的Iterator就是_list_iterator，只是还没有实例化
	public:
		reverse_iterator(Iterator it) :_it(it) {};
		//这里传入的迭代器it就会变成反向迭代器_it

		//这时候Iterator还没有实例化，不知道其就是_list_iterator，所以不能直接使用::，要加上typename提前告知有这个类型
		typename Iterator::reference operator*()
		{
			Iterator prev = _it;		//防止_it被修改
			return *(--prev);		//反向迭代器的begin指向头结点，所以反向迭代器需要--后才能使用
			//这里的*是_list_iterator中重载的*
		}

		typename Iterator::pointer operator->()
		{
			return &operator*();
		}

		self& operator++()
		{
			--_it;			//注意反向迭代器的++对于正向迭代器的--
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
		typedef _list_iterator<T, T&, T*> iterator;		//迭代器对象
		typedef _list_iterator<T, const T&, const T*> const_iterator;

		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		iterator begin()
		{
			return iterator(_head->_next);		//调用构造函数返回匿名对象
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

		//构造函数
		list()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			//data不管，因为头节点不需要存放数据
		}

		list(size_t n, const T& val = T())
		{
			_head = new Node();		//加不加括号都可以
			_head->_next = _head;
			_head->_prev = _head;
			for (size_t i = 0; i < n; i++)
			{
				push_back(val);		//扩容交给push_back
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
		//这里和上面的函数构成函数重载，这里实现是为了解决一个bug
		/*如果没有写这个函数重载，那么list(int, int)调用函数会选择调用InputIterator的
		构造函数，因为InputIterator(模板参数)比list(size_t, list)更加匹配，那么此时就会存在错误	*/

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
			list<T> tmp(st.begin(), st.end());	//构造函数的复用
			std::swap(_head, tmp._head);		//交换头结点即可
			//临时对象tmp会在函数生命周期结束时自动调用析构函数清理资源
		}

		/*传统写法
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

		list<T>& operator=(list<T> st)		//传参时复用拷贝构造
		{
			/*记录：这里我们在调试时发生了一个bug
			我们一开始传参传的是const list<T> st，此时我们调用swap函数会报错，这是因为我们参数为const对象
			使用swap相当于将const对象里面的内容修改了，所以就报错了 */
			std::swap(this->_head, st._head);
			return *this;
		}

		/*传统写法
		list& operator=(const list<T> st)
		{
			if (this != &st)	//不能上来就清空
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
				erase(it++);		//这里不能分开写(迭代器失效问题)
			}*/

			iterator it = begin();
			while (it != end())
			{
				iterator del = it++;
				delete del._node;		//_node是在list类中new出来的，这里删除借助了迭代器里面的成员_node，但是还是在list类中删除的
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
			return iterator(newNode);		//调用构造函数返回匿名对象，返回插入元素的迭代器
		}

		iterator erase(iterator pos)		//删除后，pos迭代器就失效了
		{
			assert(pos != end());
			pos._node->_prev->_next = pos._node->_next;
			pos._node->_next->_prev = pos._node->_prev;
			Node* next = pos._node->_next;
			delete pos._node;
			return iterator(next);
		}
	private:
		Node* _head;		//头结点
	};
}

