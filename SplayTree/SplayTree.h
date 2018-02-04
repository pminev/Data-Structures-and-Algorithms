#pragma once
typedef int keyType;
typedef int valType;

class SplayTree
{
public:
	SplayTree();
	SplayTree(const SplayTree&);
	SplayTree& operator=(const SplayTree&);
	~SplayTree();

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
	node * root;
};