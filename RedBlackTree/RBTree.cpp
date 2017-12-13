#include "RBTree.h"
#include <stdexcept>

RBTree::RBTree() :pRoot(nullptr)
{
}

RBTree::RBTree(const RBTree & other)
{
	copyFrom(other);
}

RBTree & RBTree::operator=(const RBTree & other)
{
	if (this != &other)
	{
		clear(pRoot);
		copyFrom(other);
	}

	return *this;
}

RBTree::~RBTree()
{
	clear(pRoot);
}

void RBTree::insert(keyType key, valueType val)
{
	insert_help(key, val, pRoot);
}

void RBTree::remove(keyType key)
{
	search(key);
	pRoot = remove_help(key, pRoot);
}

valueType RBTree::search(keyType key)
{
	return search_help(key, pRoot);
}

void RBTree::clear(node*& currNode)
{
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

void RBTree::copyFrom(const RBTree & other)
{
	copyTree_help(pRoot, other.pRoot);
}

void RBTree::copyTree_help(node *& newNode, node * oldNode)
{
	if (!oldNode)
	{
		return;
	}
	newNode = new node(oldNode->key, oldNode->value);
	copyTree_help(newNode->pLeft, oldNode->pLeft);
	copyTree_help(newNode->pRight, oldNode->pRight);
}

void RBTree::insert_help(keyType key, valueType val, node *& currNode)
{
	if (!currNode)
	{
		currNode = new node(key, val, RED);
		return;
	}

	if (key > currNode->key)
	{
		insert_help(key, val, currNode->pRight);
		currNode = validateNode(currNode);
		return;
	}

	if (key < currNode->key)
	{
		insert_help(key, val, currNode->pLeft);
		currNode = validateNode(currNode);
		return;
	}

	throw std::logic_error("Insertion failed: element with such key already exists!\n");
}

RBTree::node*& RBTree::remove_help(keyType key, node *& currNode)
{
	if (key < currNode->key)
	{
		if (!isRed(currNode->pLeft) && !isRed(currNode->pLeft->pLeft))
		{

			currNode = moveRedLeft(currNode);
		}
		currNode->pLeft = remove_help(key, currNode->pLeft);
	}
	else
	{
		if (isRed(currNode->pLeft))
		{
			currNode = rotateRight(currNode);
		}

		if ((key == currNode->key) && !currNode->pRight)
		{
			delete currNode;
			currNode = nullptr;
			return currNode;
		}

		if (!isRed(currNode->pRight) &&
			!isRed(currNode->pRight->pLeft))
		{
			currNode = moveRedRight(currNode);
		}

		if (key == currNode->key)
		{
			node* temp = currNode->pLeft;

			while (temp->pRight)
			{
				temp = temp->pRight;
			}

			currNode->key = temp->key;
			currNode->value = temp->value;

			currNode->pLeft = remove_help(currNode->key, currNode->pLeft);
		}
		else
		{
			currNode->pRight = remove_help(key, currNode->pRight);
		}
	}

	return validateNode(currNode);
}

valueType RBTree::search_help(keyType key, node *& currNode)
{
	if (!currNode)
	{
		throw std::logic_error("Operation failed: Element with such key doesn't exists!\n");
	}

	if (key == currNode->key)
	{
		return currNode->value;
	}

	if (key > currNode->key)
	{
		return search_help(key, currNode->pRight);
	}

	if (key < currNode->key)
	{
		return search_help(key, currNode->pLeft);
	}
}

RBTree::node*& RBTree::rotateLeft(node * currNode)
{
	node* tempNode = currNode->pRight;
	currNode->pRight = tempNode->pLeft;
	tempNode->pLeft = currNode;
	tempNode->color = tempNode->pLeft->color;
	tempNode->pLeft->color = RED;

	return tempNode;

}

RBTree::node*& RBTree::rotateRight(node * currNode)
{
	node* tempNode = currNode->pLeft;
	currNode->pLeft = tempNode->pRight;
	tempNode->pRight = currNode;
	tempNode->color = tempNode->pRight->color;
	tempNode->pRight->color = RED;

	return tempNode;
}

bool RBTree::isRed(node * currNode)
{
	if (!currNode)
	{
		return false;
	}
	return RED == currNode->color;
}

void RBTree::flipColors(node *& currNode)
{
	currNode->color = (currNode->color == RED) ? BLACK : RED;
	currNode->pLeft->color = (currNode->pLeft->color == RED) ? BLACK : RED;
	currNode->pRight->color = (currNode->pRight->color == RED) ? BLACK : RED;

}

RBTree::node*& RBTree::validateNode(node * currNode)
{
	if (isRed(currNode->pRight))
	{
		currNode = rotateLeft(currNode);
	}

	if (isRed(currNode->pLeft) && isRed(currNode->pLeft->pLeft))
	{
		currNode = rotateRight(currNode);
	}

	if (isRed(currNode->pRight) && isRed(currNode->pLeft))
	{
		flipColors(currNode);
	}

	return currNode;
}

RBTree::node*& RBTree::moveRedRight(node * currNode)
{
	flipColors(currNode);
	if (isRed(currNode->pLeft->pLeft))
	{
		currNode = rotateRight(currNode);
		flipColors(currNode);
	}

	return currNode;
}

RBTree::node *& RBTree::moveRedLeft(node * currNode)
{
	flipColors(currNode);
	if (isRed(currNode->pLeft->pLeft))
	{
		currNode->pRight = rotateRight(currNode->pRight);
		currNode = rotateLeft(currNode);
		flipColors(currNode);
	}
	return currNode;
}

