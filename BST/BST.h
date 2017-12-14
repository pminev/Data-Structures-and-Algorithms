#pragma once
typedef int keyType;
typedef int valueType;

/**********************************

      Classic Implementation of BST
        
***********************************/
class BST
{
private:
	struct node
	{
		keyType key;
		valueType value;
		node* pLeft;
		node* pRight;

		node(keyType k = keyType(), valueType val = valueType())
			:key(k), value(val), pLeft(nullptr), pRight(nullptr)
		{//...
		}
	};

public:
	BST();
	BST(const BST&);
	BST& operator=(const BST&);
	~BST();

	void insert(keyType key, valueType val);
	bool remove(keyType key);
	valueType search(keyType key);

private:
	void clear(node*& currNode);
	void copyFrom(const BST&);

	void copyTree_help(node*& newNode, node* oldNode);
	void insert_help(keyType key,valueType val,node*& currNode);
	bool remove_help(keyType key, node*& currNode);
	valueType search_help(keyType key, node*& currNode);

private:
	node* pRoot;
};