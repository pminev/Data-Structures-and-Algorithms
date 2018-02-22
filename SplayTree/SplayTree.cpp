#include "SplayTree.h"

SplayTree::SplayTree() :pRoot(nullptr)
{
}

SplayTree::SplayTree(const SplayTree& other)
{
	copyFrom(other);
}

SplayTree& SplayTree::operator=(const SplayTree& other)
{
	if (this != &other)
	{
		clear(pRoot);
		copyFrom(other);

	}
	return *this;
}

SplayTree::~SplayTree()
{
	clear(pRoot);
}

void SplayTree::insert(keyType key, valType val)
{
	insert_help(key, val, pRoot);
}

bool SplayTree::remove(keyType key)
{
	return remove_help(key, pRoot);
}

valType SplayTree::search(keyType key)
{
	return search_help(key, pRoot);
}

void SplayTree::clear(node*& currNode)
{
	if (currNode == nullptr)
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

void SplayTree::copyFrom(const SplayTree & other)
{
	copyTree_help(pRoot, other.pRoot);
}

void SplayTree::copyTree_help(node*& root, node* other)
{
	if (!other)
	{
		return;
	}
	root = new node(other->key, other->value);
	copyTree_help(root->pLeft, other->pLeft);
	copyTree_help(root->pRight, other->pRight);
}

void SplayTree::insert_help(keyType key, valType val, node*& root)
{
	if (!root)
	{
		root = new node(key, val);
		splay(root);
		return;
	}

	if (key > root->key)
	{
		vertices.push(root);
		insert_help(key, val, root->pRight);
		return;
	}

	if (key < root->key)
	{
		vertices.push(root);
		insert_help(key, val, root->pLeft);
		return;
	}

	throw std::logic_error("Insertion failed: element with such key already exists!\n");
}

bool SplayTree::remove_help(keyType key, node *& root)
{
	if (!root)
		throw std::logic_error("Removing failed: Element with such key doesn't exists!\n");


	if (key > root->key) {
		return remove_help(key, root->pRight);
	}

	if (key < root->key) {
		return remove_help(key, root->pLeft);
	}

	//If node doesn't have any children
	if (!root->pLeft && !root->pRight) {
		delete root;
		root = nullptr;
		return true;
	}

	//If node has two children
	if (root->pLeft && root->pRight) {
		node* temp = root->pLeft;

		while (temp->pRight) {
			temp = temp->pRight;
		}

		root->key = temp->key;
		root->value = temp->value;
		remove_help(temp->key, root->pLeft);

	}
	else { //has only one child	
		node* destroyer = root;

		if (root->pLeft)
			root = root->pLeft;
		else
			root = root->pRight;

		delete destroyer;
		return true;
	}
}

valType SplayTree::search_help(keyType key, node*& root)
{
	if (!root) {
		throw std::logic_error("Searching failed: Element with such key doesn't exists!\n");
	}

	if (key == root->key) {
		splay(root);
		return pRoot->value;	
	}

	if (key > root->key) {
		vertices.push(root);
		return search_help(key, root->pRight);
	}

	if (key < root->key) {
		vertices.push(root);
		return search_help(key, root->pLeft);
	}
}

void SplayTree::rotateLeft(node*& root,node*& parent, node*& grandParent)
{
	node* myNode = root;
	parent->pRight = root->pLeft;
	myNode->pLeft = parent;

	if (grandParent)
	{
		if (grandParent->pLeft == parent)
			grandParent->pLeft = myNode;
		else
			grandParent->pRight = myNode;
	}
	else {
		pRoot = myNode;
	}
}

void SplayTree::rotateRight(node*& root,node*& parent, node*& grandParent)
{
	node* myNode = root;
	parent->pLeft = myNode->pRight;
	myNode->pRight = parent;

	if (grandParent)
	{
		if (grandParent->pLeft == parent)
			grandParent->pLeft = myNode;
		else
			grandParent->pRight = myNode;
	} else {
		pRoot = myNode;
	}
}

void SplayTree::splay(node* root)
{
	node* parent = nullptr;
	node* gParent = nullptr;
	node* ggParent = nullptr;
	while (vertices.size())
	{
		parent = nullptr;
		gParent = nullptr;
		ggParent = nullptr;
		switch (vertices.size())
		{
		case 1:
			parent = vertices.top();
			vertices.pop();
			break;
		case 2:
			parent = vertices.top();
			vertices.pop();
			gParent = vertices.top();
			vertices.pop();
			break;
		default:
			parent = vertices.top();
			vertices.pop();
			gParent = vertices.top();
			vertices.pop();
			ggParent = vertices.top();
			break;
		}

		if (!gParent) {
			if (parent->pLeft == root)
				rotateRight(root,parent, gParent);
			else
				rotateLeft(root,parent, gParent);
		}
		else if (parent->pLeft == root && gParent->pLeft == parent) {
			rotateRight(parent,gParent, ggParent);
			if (!ggParent)
				gParent = nullptr;
			else
				gParent = ggParent;
			node* s = root;
			rotateRight(s,parent, gParent);
		}
		else if (parent->pRight == root && gParent->pRight == parent) {
			rotateLeft(parent,gParent, ggParent);
			if (!ggParent)
				gParent = nullptr;
			rotateLeft(root,parent, gParent);
		}
		else if (parent->pLeft==root&& gParent->pRight==parent){
			rotateRight(root,parent, gParent);
			rotateLeft(root,gParent, ggParent);
		}
		else {
			rotateLeft(root,parent, gParent);
			rotateRight(root,gParent, ggParent);
		}


	}
}
