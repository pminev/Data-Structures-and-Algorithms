#include "BST.h"
#include <stdexcept>

BST::BST():pRoot(nullptr)
{
}

BST::BST(const BST & other)
{
	copyFrom(other);
}

BST & BST::operator=(const BST & other)
{
	if (this!=&other)
	{
		clear(pRoot);
		copyFrom(other);
	}

	return *this;
}

BST::~BST()
{
	clear(pRoot);
}

void BST::insert(keyType key, valueType val)
{
	insert_help(key, val, pRoot);
}

bool BST::remove(keyType key)
{
	return remove_help(key, pRoot);
}

valueType BST::search(keyType key)
{
		return search_help(key, pRoot);
}

void BST::clear(node*& currNode)
{
	if(currNode==nullptr)
	{
		return;
	}
	
	if (currNode->pLeft)
	{
		clear(currNode->pLeft);
	}

	if (currNode->pRight)
	{
		clear(currNode->pRight);
	}

	delete currNode;
	currNode = nullptr;
}

void BST::copyFrom(const BST & other)
{
	copyTree_help(pRoot, other.pRoot);
}

void BST::copyTree_help(node *& newNode, node * oldNode)
{
	if (!oldNode)
	{
		return;
	}
	newNode = new node(oldNode->key, oldNode->value);
	copyTree_help(newNode->pLeft, oldNode->pLeft);
	copyTree_help(newNode->pRight, oldNode->pRight);
}

void BST::insert_help(keyType key, valueType val, node *& currNode)
{
	if (!currNode)
	{
		currNode = new node(key, val);
		return;
	}

	if (key>currNode->key)
	{
		insert_help(key, val, currNode->pRight);
		return;
	}

	if (key<currNode->key)
	{
		insert_help(key, val, currNode->pLeft);
		return;
	}

	throw std::logic_error("Insertion failed: element with such key already exists!\n");
}

bool BST::remove_help(keyType key, node *& currNode)
{
	if (!currNode)
	{
		throw std::logic_error("Removing failed: Element with such key doesn't exists!\n");
	}

	if (key>currNode->key)
	{
		return remove_help(key, currNode->pRight);		 
	}

	if (key<currNode->key)
	{
		return remove_help(key, currNode->pLeft);		 
	}

	//If node doesn't have any children
	if (!currNode->pLeft && !currNode->pRight)
	{
		delete currNode;
		currNode = nullptr;
		return true;
	}

	//If node has two children
	if (currNode->pLeft && currNode->pRight)
	{
		node* temp = currNode->pLeft;

		while (temp->pRight)
		{
			temp = temp->pRight;
		}

		currNode->key = temp->key;
		currNode->value = temp->value;
		remove_help(temp->key, currNode->pLeft);

	}
	else  //has only one child
	{
		node* destroyer = currNode;
		
		if (currNode->pLeft)
			currNode = currNode->pLeft;
		else 
			currNode = currNode->pRight;

		delete destroyer; 

	}

}

valueType BST::search_help(keyType key, node *& currNode)
{
	if (!currNode)
	{
		throw std::logic_error("Searching failed: Element with such key doesn't exists!\n");
	}

	if (key==currNode->key)
	{
		return currNode->value;
	}

	if (key>currNode->key)
	{
		return search_help(key, currNode->pRight);
	}

	if (key<currNode->key)
	{
		return search_help(key, currNode->pLeft);
	}
}
