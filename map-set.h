#pragma once
#include <iostream>
#include <cassert>
using namespace std;

//用一颗红黑树同时封装set和map
/*节点模板参数的控制
我们实现的节点模板为template<class K, class V>:k为键值，v为value值
但是由于我们是一颗红黑树实现两个容器map和set，并且set中的value值就是key值，map中的value值为pair<key, value>
所以我们这里将节点的模板设为T以便统一，在set中T = K，在map中T = pair<K, V>
所以在底层的红黑树模板参数中，我们原来实现为template<class K, class V>，这里V就变成了T	*/

enum Color
{
	RED,
	BLACK
};

//在节点中只有一个T模板类型，在set容器中就是data就是key，在map容器中data就是pair<K, V>
template<class T>
struct RBTreeNode
{
	RBTreeNode<T>* parent;
	RBTreeNode<T>* left;
	RBTreeNode<T>* right;
	T data;
	Color color;
	RBTreeNode(const T& data) :
		data(data), parent(nullptr), left(nullptr), right(nullptr), color(RED)
	{}
};

//这里需要先声明一下迭代器
template<class T, class Ref, class Ptr>
class TreeIterator;
template<class Iterator>
class ReverseIterator;
/*KeyOfT:表示仿函数模板参数
仿函数的作用:通过节点的data从而获取节点的key值，在set中其实用处不大因为data就是key值，但map中需要	*/
template<class K, class T, class KeyOfT>		//这里的模板T表示节存储的data的数据类型
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef TreeIterator<T, T&, T*> iterator;		//正向迭代器
	typedef TreeIterator<T, const T&, const T*> const_iterator;		//const正向迭代器
	typedef ReverseIterator<iterator> reverse_iterator;		//反向迭代器
	typedef ReverseIterator<const_iterator> const_reverse_iterator;

	reverse_iterator rbegin()
	{
		//返回红黑树最右节点的方向迭代器
		Node* right = root;
		while (right && right->right)
		{
			right = right->right;
		}
		return reverse_iterator(iterator(right));		//返回匿名对象(不能引用接收)
	}

	reverse_iterator rend()
	{
		//不严谨
		return reverse_iterator(iterator(nullptr));
	}

	//begin()的迭代器为红黑树最左边的节点
	iterator begin()
	{
		Node* left = root;
		while (left && left->left)
		{
			left = left->left;
		}
		return iterator(left);
	}

	iterator end()
	{
		//不严谨
		return iterator(nullptr);
	}

	/*为什么说上面的迭代器不严谨呢?
	因为理论上我们对end()位置的正向迭代器进行--操作后，应该得到最后一个结点的正向迭代器
	但我们实现end()时，是直接返回由nullptr构造得到的正向迭代器的，因此上述实现的代码无法完成此操作

	C++SLT库当中的实现逻辑：C++STL库当中实现红黑树时，在红黑树的根结点处增加了一个头结点
	该头结点的左指针指向红黑树当中的最左结点，右指针指向红黑树当中的最右结点，父指针指向红黑树的根结点
	在该结构下，实现begin()时，直接用头结点的左孩子构造一个正向迭代器即可
	实现rbegin()时，直接用头结点的右孩子构造一个反向迭代器即可(实际是先用该结点构造一个正向迭代器，再用正向迭代器构造出反向迭代器)
	而实现end()和rend()时，直接用头结点构造出正向和反向迭代器即可
	此后，通过对逻辑的控制，就可以实现end()进行--操作后得到最后一个结点的正向迭代器
	但实现该结构需要更改当前很多函数的逻辑，例如插入结点时，若插入到了红黑树最左结点的左边，或最右结点的右边
	此时需要更新头结点左右指针的指向，这里就不进行实际实现了
	C++STL库的实现逻辑：http://t.csdn.cn/49PPH		*/

	//构造函数
	RBTree() :root(nullptr) {}

	//拷贝构造
	RBTree(const RBTree<K, T, KeyOfT>& rbTree)
	{
		_Copy(rbTree.root, nullptr);
	}

private:
	Node* _Copy(Node* root, Node* parent)
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		Node* newNode = new Node(root->data);
		newNode->parent = parent;
		newNode->left = _Copy(root->left, newNode);
		newNode->right = _Copy(root->right, newNode);
		return newNode;
	}

public:
	//赋值重载
	RBTree<K, T, KeyOfT>& operator=(RBTree<K, T, KeyOfT> rbtree)
	{
		::swap(root, rbtree.root);
		return *this;
	}

	~RBTree()
	{
		_Destory(root);
		root = nullptr;
	}

private:
	void _Destory(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_Destory(root->left);
		_Destory(root->right);
		delete root;
	}

public:
	iterator find(const K& key)
	{
		KeyOfT kot;		//通过仿函数获取节点键值
		Node* cur = root;
		while (cur)
		{
			if (key > kot(cur->data))
			{
				cur = cur->right;
			}
			else if (key < kot(cur->data))
			{
				cur = cur->left;
			}
			else return iterator(cur);		//查找成功，返回匿名对象(匿名对象作为返回值不能引用)
		}
		return end();		//查找失败
	}

	pair<iterator, bool> Insert(const T& data)
	{
		if (root == nullptr)
		{
			root = new Node(data);
			root->color = BLACK;
			return std::make_pair(iterator(root), true);
		}

		KeyOfT kot;
		Node* cur = root;
		Node* parent = nullptr;
		while (cur)
		{
			if (kot(cur->data) > kot(data))
			{
				parent = cur;
				cur = cur->left;
			}
			else if (kot(cur->data) < kot(data))
			{
				parent = cur;
				cur = cur->right;
			}
			else
				return std::make_pair(iterator(cur), false);
		}
		cur = new Node(data);
		Node* newNode = cur;
		cur->parent = parent;
		if (kot(parent->data) > kot(data))
		{
			parent->left = cur;
		}
		else if (kot(parent->data) < kot(data))
		{
			parent->right = cur;
		}
		else assert(false);
		while (parent && parent->color == RED)
		{
			Node* grandparent = parent->parent;		

			if (grandparent->left == parent)		//uncle是右孩子(uncle为parent的兄弟节点)
			{
				Node* uncle = grandparent->right;

				if (uncle && uncle->color == RED)		//uncle存在且为RED(不需要旋转，只用调整颜色，然后向上调整)
				{
					grandparent->color = RED;
					uncle->color = parent->color = BLACK;
					if (grandparent->parent && grandparent->parent->color == RED)		//避免grandparent为root，导致访问其父节点时是访问空指针
					{
						cur = grandparent;
						parent = cur->parent;
					}
				}
				else	//uncle不存在或者uncle为黑(这里两种情况都不用管uncle，所以可以一起处理)
				{
					if (parent->left == cur)		//直线(只用单右旋)
					{
						RotateR(grandparent);
						//调整颜色
						parent->color = BLACK;
						grandparent->color = RED;
					}

					else if (parent->right == cur)
					{
						RotateL(parent);		//先变成直线
						RotateR(grandparent);

						cur->color = BLACK;
						grandparent->color = RED;
					}
					break;		//因为我们将旋转后的grandparent(此grandparent非彼grandparent)的颜色变成了BLACK，所以可以直接跳出循环不用向上调整
				}
			}
			if (grandparent->right == parent)		//uncle为左节点
			{
				Node* uncle = grandparent->left;
				if (uncle && uncle->color == RED)		//不需要旋转，只用调整颜色
				{
					parent->color = uncle->color = BLACK;
					grandparent->color = RED;

					cur = grandparent;
					parent = cur->parent;
				}
				else
				{
					if (parent->right == cur)		//直线
					{
						RotateL(grandparent);
						parent->color = BLACK;
						grandparent->color = RED;
					}
					else if (parent->left == cur)	//折线
					{
						RotateR(parent);
						RotateL(grandparent);

						cur->color = BLACK;
						grandparent->color = RED;
					}
					break;
				}
			}

		}
		root->color = BLACK;		//避免了grandparent为root，并且将其颜色修改成RED的情况
		return std::make_pair(iterator(newNode), true);
	}
private:
	void RotateR(Node* parent)
	{
		Node* subL = parent->left;
		Node* subLR = subL->right;
		parent->left = subLR;
		subL->right = parent;
		Node* pparent = parent->parent;
		parent->parent = subL;
		if (subLR)
		{
			subLR->parent = parent;
		}
		if (parent == root)
		{
			root = subL;
			subL->parent = nullptr;
		}
		else
		{
			if (pparent->left == parent)
			{
				pparent->left = subL;
			}
			else if (pparent->right == parent)
			{
				pparent->right = subL;
			}
			else assert(false);
			subL->parent = pparent;
		}
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->right;
		Node* subRL = subR->left;
		Node* pparent = parent->parent;
		subR->left = parent;
		parent->parent = subR;
		parent->right = subRL;
		if (subRL)
		{
			subRL->parent = parent;
		}
		if (parent == root)
		{
			root = subR;
			subR->parent = nullptr;
		}
		else
		{
			if (pparent->left == parent)
			{
				pparent->left = subR;
			}
			else if (pparent->right == parent)
			{
				pparent->right = subR;
			}
			subR->parent = pparent;
		}
	}

public:
	bool Erase(const K& key)
	{
		Node* parent = nullptr;
		Node* cur = root;
		Node* del = nullptr;
		Node* delparent = nullptr;
		KeyOfT kot;
		while (cur)
		{
			if (kot(cur->data) > key)
			{
				parent = cur;
				cur = cur->left;
			}
			else if (kot(cur->data) < key)
			{
				parent = cur;
				cur = cur->right;
			}
			else
			{
				if (cur->left == nullptr)
				{
					if (cur == root)
					{
						root = cur->right;
						if (root)
						{
							root->color = BLACK;
							root->parent = nullptr;
						}
						delete cur;
						return true;
					}
					else
					{
						del = cur;
						delparent = parent;
						break;
					}
				}
				else if (cur->right == nullptr)
				{
					if (parent == nullptr)
					{
						root = cur->left;
						if (root)
						{
							root->color = BLACK;
							root->parent = nullptr;
						}
						delete cur;
						return true;
					}
					else
					{
						del = cur;
						delparent = parent;
						break;
					}
				}
				else
				{
					Node* maxNode = cur->left;
					Node* maxParent = cur;
					while (maxNode->right)
					{
						maxParent = maxNode;
						maxNode = maxNode->right;
					}
					std::swap(cur->data, maxNode->data);
					del = maxNode;
					delparent = maxParent;
					break;
				}
			}
		}
		if (cur == nullptr)
		{
			return false;
		}
		Node* realdel = del;
		Node* realdelparent = delparent;
		if (del->color == BLACK)		//删除的是黑色节点
		{
			//注意：这里我们删除节点只有可能是叶子节点和单支节点(前面已经做了调整)

			if (del->left)		//删除节点有左子树(此时删除节点的左孩子肯定是红色)
			{
				//先只改变颜色，不改变其父亲指针
				del->left->color = BLACK;
			}
			else if (del->right)
			{
				del->right->color = BLACK;
			}
			//删除的是黑色叶子节点
			else if (del->left == nullptr && del->right == nullptr)
			{
				while (del != root)		//可能需要向上调整
				{
					//兄弟节点为右孩子
					if (delparent->left == del)
					{
						Node* brother = delparent->right;
						//情况1. brother为红
						if (brother->color == RED)
						{
							brother->color = BLACK;
							delparent->color = RED;
							RotateL(delparent);			//先更改颜色后旋转，不然brother里面的指针指向会变化

							//需要继续处理
							brother = delparent->right;		//左旋之后del的兄弟节点变了(变成了之前的brother->left)
						}

						//情况2. brother为黑，brother的左右孩子都为空或者都为黑
						if ((brother->left == nullptr || brother->left->color == BLACK) &&
							(brother->right == nullptr || brother->right->color == BLACK))
						{
							//parent为红，调整后不需要向上调整
							if (delparent->color == RED)
							{
								delparent->color = BLACK;
								brother->color = RED;
								break;
							}

							//如果parent为黑，将brother变红后继续调整
							brother->color = RED;
							del = delparent;
							delparent = del->parent;
						}
						else
						{
							//情况3. brother->right为红，brother->left为BLACK或NIL
							if ((brother->right == nullptr) || (brother->right->color == BLACK))
							{
								brother->left->color = BLACK;
								brother->color = RED;
								RotateR(brother);

								//brother = brother->right;		//error，这里旋转后，brother的右孩子就不是原来的了，所以不能这样子
								brother = delparent->right;		//画图
							}
							//情况3处理后，一定会变成情况4,

							//情况4. brother->left为红，brother->right为任意
							brother->color = delparent->color;
							delparent->color = BLACK;
							brother->right->color = BLACK;
							RotateL(delparent);
							break;		//此时必定调整完必
						}
					}

					else if (delparent->right == del)
					{
						Node* brother = delparent->left;

						if (brother->color == RED)
						{
							delparent->color = RED;
							brother->color = BLACK;
							RotateR(delparent);

							brother = delparent->left;
						}

						if ((brother->left == nullptr || brother->left->color == BLACK)
							&& (brother->right == nullptr || brother->right->color == BLACK))
						{
							if (delparent->color == RED)
							{
								delparent->color = BLACK;
								brother->color = RED;
								break;
							}

							//让非del路径的黑色节点减少一个然后向上调整
							brother->color = RED;
							del = delparent;
							delparent = del->parent;
						}

						else
						{
							if ((brother->left->color == BLACK) || (brother->left == nullptr || brother->right->color == BLACK))
							{
								brother->right->color = BLACK;
								brother->color = RED;
								RotateL(brother);

								brother = delparent->left;
							}

							brother->color = delparent->color;
							delparent->color = BLACK;
							brother->color = BLACK;
							RotateR(delparent);
							break;
						}
					}
				}
			}
		}
		if (realdel->right == nullptr)
		{
			if (realdelparent->left == realdel)
			{
				realdelparent->left = realdel->left;
				if (realdel->left)
				{
					realdel->left->parent = realdelparent;
				}
			}
			else
			{
				realdelparent->right = realdel->left;
				if (realdel->left)
				{
					realdel->left->parent = realdelparent;
				}
			}
		}
		else
		{
			if (realdelparent->left == realdel)
			{
				realdelparent->left = realdel->right;
				if (realdel->right)
				{
					realdel->right->parent = realdelparent;
				}
			}
			else
			{
				realdelparent->right = realdel->right;
				if (realdel->right)
				{
					realdel->right->parent = realdelparent;
				}
			}
		}
		delete realdel;
		return true;
	}
private:
	Node* root;
};

//正向迭代器
template<class T, class Ref, class Ptr>
class TreeIterator
{
private:
	typedef RBTreeNode<T> Node;
	typedef Ref Reference;
	typedef Ptr Pointer;
	typedef TreeIterator<T, Ref, Ptr> self;
public:
	TreeIterator(Node* node) :node(node) {}

	Ptr operator->()
	{
		return &(node->data);
	}

	Ref operator*()
	{
		return node->data;
	}

	//前置++(找到比当前迭代器元素大的元素集合中最小的那个)
	self& operator++()
	{
		//节点右子树不为空
		if (node->right)
		{
			Node* left = node->right;
			while (left->left)
			{
				left = left->left;
			}
			node = left;
		}
		else	//节点的右子树为空
		{
			//找孩子是父亲左孩子的祖先
			Node* cur = node;
			Node* parent = node->parent;
			while (parent && parent->right == cur)
			{
				cur = parent;
				parent = cur->parent;
			}
			node = parent;
		}
		return *this;
	}

	//前置--(找到比当前迭代器元素小的元素集合中最大的那个)
	self& operator--()
	{
		if (node->left)
		{
			Node* right = node->left;
			while (right->right)
			{
				right = right->right;
			}
			node = right;
		}
		else
		{
			Node* cur = node;
			Node* parent = node->parent;
			while (parent && parent->left == cur)
			{
				cur = parent;
				parent = cur->parent;
			}
			node = parent;
		}
		return *this;
	}

	//后置++
	self operator++(int)
	{
		Node* tmp = node;
		if (node->right)
		{
			Node* left = node->right;
			while (left->left)
			{
				left = left->left;
			}
			node = left;
		}
		else
		{
			Node* cur = node;
			Node* parent = node->parent;
			while (parent && parent->right == cur)
			{
				cur = parent;
				parent = cur->parent;
			}
			node = parent;
		}
		return TreeIterator(tmp);
	}

	//后置--
	self operator--(int)
	{
		Node* tmp = node;
		if (node->left)
		{
			Node* right = node->left;
			while (right->right)
			{
				right = right->right;
			}
			node = right;
		}
		else
		{
			Node* cur = node;
			Node* parent = node->parent;
			while (parent && parent->left == cur)
			{
				cur = parent;
				parent = cur->parent;
			}
			node = parent;
		}
		return TreeIterator(tmp);
	}

	bool operator==(const self& it)
	{
		return node == it.node;
	}

	bool operator!=(const self& it)
	{
		return node != it.node;
	}
private:
	Node* node;
};

//反向迭代器(适配器)
template<class Iterator>
class ReverseIterator
{
	typedef typename Iterator::reference Ref;
	typedef typename Iterator::Pointer Ptr;
	typedef ReverseIterator<Iterator> self;
public:
	Ref operator*()
	{
		return *it;
	}

	Ptr operator->()
	{
		return it.operator->();
	}

	self& operator++()
	{
		return --it;
	}

	self& operator--()
	{
		return ++it;
	}

	self operator++(int)
	{
		return it--;
	}

	self operator--(int)
	{
		return it++;
	}

	bool operator==(const self& it)
	{
		return this->it == it.it;
	}

	bool operator!=(const self& it)
	{
		return this->it != it.it;
	}
private:
	Iterator it;
};

namespace yw
{
	template<class K>
	class set
	{
		//仿函数(通过其获取容器的键值)，该类为内部类并且是private属性，外面无法单独访问到，只能内部使用
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;			//set容器中直接返回key值
			}
		};
	public:
		//要加上typename告诉其这是一个类型:https://zhuanlan.zhihu.com/p/335777990
		typedef typename RBTree<K, K, SetKeyOfT>::iterator iterator;			//正向迭代器
		typedef typename RBTree<K, K, SetKeyOfT>::reverse_iterator reverse_iterator;	//反向迭代器

		//这里不用写构造函数，因为我们创建set对象时，会调用红黑树的构造函数
		iterator begin()
		{
			return set_RBTree.begin();
		}

		iterator end()
		{
			return set_RBTree.end();
		}

		reverse_iterator rbegin()
		{
			return set_RBTree.rbegin();
		}

		reverse_iterator rend()
		{
			return set_RBTree.rend();
		}

		//插入insert
		pair<iterator, bool> insert(const K& key)
		{
			return set_RBTree.Insert(key);
		}

		//删除erase
		void erase(const K& key)
		{
			set_RBTree.Erase(key);
		}

		//查找find
		iterator find(const K& key)
		{
			return set_RBTree.find(key);
		}
	private:
		RBTree<K, K, SetKeyOfT> set_RBTree;		//内部存储的是一颗红黑树
	};


	template<class K, class V>
	class map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};

		//typedef pair<const K, V> type_value;		//标准STL里面就是这样子定义的，注意这里的K要加const属性，表示不能修改
	public:
		typedef typename RBTree<K, pair<K, V>, MapKeyOfT>::iterator iterator;
		typedef typename RBTree<K, pair<K, V>, MapKeyOfT>::reverse_iterator reverse_iterator;

		iterator begin()
		{
			return map_RBTree.begin();
		}

		iterator end()
		{
			return map_RBTree.end();
		}

		reverse_iterator rbegin()
		{
			return map_RBTree.rbegin();
		}

		reverse_iterator rend()
		{
			return map_RBTree.rend();
		}

		pair<iterator, bool> insert(const pair<K, V>& kv)
		{
			return map_RBTree.Insert(kv);
		}

		void erase(const K& key)
		{
			map_RBTree.Erase(key);
		}

		iterator find(const K& key)
		{
			return map_RBTree.find(key);
		}

		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = insert(make_pair(key, V()));
			iterator it = ret.first;
			return it->second;
		}
	private:
		RBTree<K, pair<K, V>, MapKeyOfT> map_RBTree;		//第二个类型是对组，因为第二个类型就是节点的data类型，节点在map中存放对组
	};
}

//总结：其是map和set容器内部就是一个空壳，其函数接口的实现都是在一颗红黑树的内部
