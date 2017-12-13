#pragma once
typedef int keyType;
typedef int valueType;

enum TreeColor {
	RED = 0,
	BLACK = 1
};

/*************************************************
          LEFT LEANING RED-BLACK TREE
		(ROBERT SEDGEWICK'S ALGORYTHM)
**************************************************/
class RBTree
{
private:
	struct node
	{
		keyType key;
		valueType value;
		node* pLeft;
		node* pRight;
		TreeColor color;

		node(keyType k = keyType(), valueType val = valueType(), TreeColor col = BLACK)
			:key(k), value(val), pLeft(nullptr), pRight(nullptr),color(col)
		{//...
		}
	};

public:
	RBTree();
	RBTree(const RBTree&);
	RBTree& operator=(const RBTree&);
	~RBTree();

	void insert(keyType key, valueType val);
	void remove(keyType key);
	valueType search(keyType key);

private:
	void clear(node*& currNode);
	void copyFrom(const RBTree&);

	void copyTree_help(node*& newNode, node* oldNode);
	void insert_help(keyType key, valueType val, node*& currNode);
	node*& remove_help(keyType key, node*& currNode);
	valueType search_help(keyType key, node*& currNode);

	node*& rotateLeft(node* currNode);
	node*& rotateRight(node* currNode);
	bool isRed(node* currNode);
	void flipColors(node*& currNode);
	node*& validateNode(node* currNode);

	node*& moveRedRight(node* currNode);
	node*& moveRedLeft(node* currNode);

private:
	node* pRoot;
};