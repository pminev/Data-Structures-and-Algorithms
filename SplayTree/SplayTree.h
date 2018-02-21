#pragma once
#include <stack>
typedef int keyType;
typedef int valType;

class SplayTree
{
public:
	SplayTree();
	SplayTree(const SplayTree&);
	SplayTree& operator=(const SplayTree&);
	~SplayTree();

	void insert(keyType key, valType val);
	bool remove(keyType key);
	valType search(keyType key);

private:
	struct node {
		keyType key;
		valType value;
		node* pLeft;
		node* pRight;

		node(keyType k, valType v)
			:key(k), value(v), pLeft(nullptr), pRight(nullptr) 
		{
			//.......
		}

	};

private:
	void clear(node*&);
	void copyFrom(const SplayTree&);

	void copyTree_help(node*&, node*);
	void insert_help(keyType, valType, node*&);
	bool remove_help(keyType, node*&);
	valType search_help(keyType, node*&);

	void rotateLeft(node*&,node*&);
	void rotateRight(node*&,node*&);
	void splay(node*&);

private:
	node* pRoot;
	std::stack<node*> vertices;
};