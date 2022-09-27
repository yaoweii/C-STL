#pragma once
#include <iostream>
#include <cassert>
using namespace std;

//��һ�ź����ͬʱ��װset��map
/*�ڵ�ģ������Ŀ���
����ʵ�ֵĽڵ�ģ��Ϊtemplate<class K, class V>:kΪ��ֵ��vΪvalueֵ
��������������һ�ź����ʵ����������map��set������set�е�valueֵ����keyֵ��map�е�valueֵΪpair<key, value>
�����������ｫ�ڵ��ģ����ΪT�Ա�ͳһ����set��T = K����map��T = pair<K, V>
�����ڵײ�ĺ����ģ������У�����ԭ��ʵ��Ϊtemplate<class K, class V>������V�ͱ����T	*/

enum Color
{
	RED,
	BLACK
};

//�ڽڵ���ֻ��һ��Tģ�����ͣ���set�����о���data����key����map������data����pair<K, V>
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

//������Ҫ������һ�µ�����
template<class T, class Ref, class Ptr>
class TreeIterator;
template<class Iterator>
class ReverseIterator;
/*KeyOfT:��ʾ�º���ģ�����
�º���������:ͨ���ڵ��data�Ӷ���ȡ�ڵ��keyֵ����set����ʵ�ô�������Ϊdata����keyֵ����map����Ҫ	*/
template<class K, class T, class KeyOfT>		//�����ģ��T��ʾ�ڴ洢��data����������
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef TreeIterator<T, T&, T*> iterator;		//���������
	typedef TreeIterator<T, const T&, const T*> const_iterator;		//const���������
	typedef ReverseIterator<iterator> reverse_iterator;		//���������
	typedef ReverseIterator<const_iterator> const_reverse_iterator;

	reverse_iterator rbegin()
	{
		//���غ�������ҽڵ�ķ��������
		Node* right = root;
		while (right && right->right)
		{
			right = right->right;
		}
		return reverse_iterator(iterator(right));		//������������(�������ý���)
	}

	reverse_iterator rend()
	{
		//���Ͻ�
		return reverse_iterator(iterator(nullptr));
	}

	//begin()�ĵ�����Ϊ���������ߵĽڵ�
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
		//���Ͻ�
		return iterator(nullptr);
	}

	/*Ϊʲô˵����ĵ��������Ͻ���?
	��Ϊ���������Ƕ�end()λ�õ��������������--������Ӧ�õõ����һ���������������
	������ʵ��end()ʱ����ֱ�ӷ�����nullptr����õ�������������ģ��������ʵ�ֵĴ����޷���ɴ˲���

	C++SLT�⵱�е�ʵ���߼���C++STL�⵱��ʵ�ֺ����ʱ���ں�����ĸ���㴦������һ��ͷ���
	��ͷ������ָ��ָ���������е������㣬��ָ��ָ���������е����ҽ�㣬��ָ��ָ�������ĸ����
	�ڸýṹ�£�ʵ��begin()ʱ��ֱ����ͷ�������ӹ���һ���������������
	ʵ��rbegin()ʱ��ֱ����ͷ�����Һ��ӹ���һ���������������(ʵ�������øý�㹹��һ����������������������������������������)
	��ʵ��end()��rend()ʱ��ֱ����ͷ��㹹�������ͷ������������
	�˺�ͨ�����߼��Ŀ��ƣ��Ϳ���ʵ��end()����--������õ����һ���������������
	��ʵ�ָýṹ��Ҫ���ĵ�ǰ�ܶຯ�����߼������������ʱ�������뵽�˺�������������ߣ������ҽ����ұ�
	��ʱ��Ҫ����ͷ�������ָ���ָ������Ͳ�����ʵ��ʵ����
	C++STL���ʵ���߼���http://t.csdn.cn/49PPH		*/

	//���캯��
	RBTree() :root(nullptr) {}

	//��������
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
	//��ֵ����
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
		KeyOfT kot;		//ͨ���º�����ȡ�ڵ��ֵ
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
			else return iterator(cur);		//���ҳɹ���������������(����������Ϊ����ֵ��������)
		}
		return end();		//����ʧ��
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

			if (grandparent->left == parent)		//uncle���Һ���(uncleΪparent���ֵܽڵ�)
			{
				Node* uncle = grandparent->right;

				if (uncle && uncle->color == RED)		//uncle������ΪRED(����Ҫ��ת��ֻ�õ�����ɫ��Ȼ�����ϵ���)
				{
					grandparent->color = RED;
					uncle->color = parent->color = BLACK;
					if (grandparent->parent && grandparent->parent->color == RED)		//����grandparentΪroot�����·����丸�ڵ�ʱ�Ƿ��ʿ�ָ��
					{
						cur = grandparent;
						parent = cur->parent;
					}
				}
				else	//uncle�����ڻ���uncleΪ��(����������������ù�uncle�����Կ���һ����)
				{
					if (parent->left == cur)		//ֱ��(ֻ�õ�����)
					{
						RotateR(grandparent);
						//������ɫ
						parent->color = BLACK;
						grandparent->color = RED;
					}

					else if (parent->right == cur)
					{
						RotateL(parent);		//�ȱ��ֱ��
						RotateR(grandparent);

						cur->color = BLACK;
						grandparent->color = RED;
					}
					break;		//��Ϊ���ǽ���ת���grandparent(��grandparent�Ǳ�grandparent)����ɫ�����BLACK�����Կ���ֱ������ѭ���������ϵ���
				}
			}
			if (grandparent->right == parent)		//uncleΪ��ڵ�
			{
				Node* uncle = grandparent->left;
				if (uncle && uncle->color == RED)		//����Ҫ��ת��ֻ�õ�����ɫ
				{
					parent->color = uncle->color = BLACK;
					grandparent->color = RED;

					cur = grandparent;
					parent = cur->parent;
				}
				else
				{
					if (parent->right == cur)		//ֱ��
					{
						RotateL(grandparent);
						parent->color = BLACK;
						grandparent->color = RED;
					}
					else if (parent->left == cur)	//����
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
		root->color = BLACK;		//������grandparentΪroot�����ҽ�����ɫ�޸ĳ�RED�����
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
		if (del->color == BLACK)		//ɾ�����Ǻ�ɫ�ڵ�
		{
			//ע�⣺��������ɾ���ڵ�ֻ�п�����Ҷ�ӽڵ�͵�֧�ڵ�(ǰ���Ѿ����˵���)

			if (del->left)		//ɾ���ڵ���������(��ʱɾ���ڵ�����ӿ϶��Ǻ�ɫ)
			{
				//��ֻ�ı���ɫ�����ı��丸��ָ��
				del->left->color = BLACK;
			}
			else if (del->right)
			{
				del->right->color = BLACK;
			}
			//ɾ�����Ǻ�ɫҶ�ӽڵ�
			else if (del->left == nullptr && del->right == nullptr)
			{
				while (del != root)		//������Ҫ���ϵ���
				{
					//�ֵܽڵ�Ϊ�Һ���
					if (delparent->left == del)
					{
						Node* brother = delparent->right;
						//���1. brotherΪ��
						if (brother->color == RED)
						{
							brother->color = BLACK;
							delparent->color = RED;
							RotateL(delparent);			//�ȸ�����ɫ����ת����Ȼbrother�����ָ��ָ���仯

							//��Ҫ��������
							brother = delparent->right;		//����֮��del���ֵܽڵ����(�����֮ǰ��brother->left)
						}

						//���2. brotherΪ�ڣ�brother�����Һ��Ӷ�Ϊ�ջ��߶�Ϊ��
						if ((brother->left == nullptr || brother->left->color == BLACK) &&
							(brother->right == nullptr || brother->right->color == BLACK))
						{
							//parentΪ�죬��������Ҫ���ϵ���
							if (delparent->color == RED)
							{
								delparent->color = BLACK;
								brother->color = RED;
								break;
							}

							//���parentΪ�ڣ���brother�����������
							brother->color = RED;
							del = delparent;
							delparent = del->parent;
						}
						else
						{
							//���3. brother->rightΪ�죬brother->leftΪBLACK��NIL
							if ((brother->right == nullptr) || (brother->right->color == BLACK))
							{
								brother->left->color = BLACK;
								brother->color = RED;
								RotateR(brother);

								//brother = brother->right;		//error��������ת��brother���Һ��ӾͲ���ԭ�����ˣ����Բ���������
								brother = delparent->right;		//��ͼ
							}
							//���3�����һ���������4,

							//���4. brother->leftΪ�죬brother->rightΪ����
							brother->color = delparent->color;
							delparent->color = BLACK;
							brother->right->color = BLACK;
							RotateL(delparent);
							break;		//��ʱ�ض��������
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

							//�÷�del·���ĺ�ɫ�ڵ����һ��Ȼ�����ϵ���
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

//���������
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

	//ǰ��++(�ҵ��ȵ�ǰ������Ԫ�ش��Ԫ�ؼ�������С���Ǹ�)
	self& operator++()
	{
		//�ڵ���������Ϊ��
		if (node->right)
		{
			Node* left = node->right;
			while (left->left)
			{
				left = left->left;
			}
			node = left;
		}
		else	//�ڵ��������Ϊ��
		{
			//�Һ����Ǹ������ӵ�����
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

	//ǰ��--(�ҵ��ȵ�ǰ������Ԫ��С��Ԫ�ؼ����������Ǹ�)
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

	//����++
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

	//����--
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

//���������(������)
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
		//�º���(ͨ�����ȡ�����ļ�ֵ)������Ϊ�ڲ��ಢ����private���ԣ������޷��������ʵ���ֻ���ڲ�ʹ��
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;			//set������ֱ�ӷ���keyֵ
			}
		};
	public:
		//Ҫ����typename����������һ������:https://zhuanlan.zhihu.com/p/335777990
		typedef typename RBTree<K, K, SetKeyOfT>::iterator iterator;			//���������
		typedef typename RBTree<K, K, SetKeyOfT>::reverse_iterator reverse_iterator;	//���������

		//���ﲻ��д���캯������Ϊ���Ǵ���set����ʱ������ú�����Ĺ��캯��
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

		//����insert
		pair<iterator, bool> insert(const K& key)
		{
			return set_RBTree.Insert(key);
		}

		//ɾ��erase
		void erase(const K& key)
		{
			set_RBTree.Erase(key);
		}

		//����find
		iterator find(const K& key)
		{
			return set_RBTree.find(key);
		}
	private:
		RBTree<K, K, SetKeyOfT> set_RBTree;		//�ڲ��洢����һ�ź����
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

		//typedef pair<const K, V> type_value;		//��׼STL������������Ӷ���ģ�ע�������KҪ��const���ԣ���ʾ�����޸�
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
		RBTree<K, pair<K, V>, MapKeyOfT> map_RBTree;		//�ڶ��������Ƕ��飬��Ϊ�ڶ������;��ǽڵ��data���ͣ��ڵ���map�д�Ŷ���
	};
}

//�ܽ᣺����map��set�����ڲ�����һ���տǣ��亯���ӿڵ�ʵ�ֶ�����һ�ź�������ڲ�
