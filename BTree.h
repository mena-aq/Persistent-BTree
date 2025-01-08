#ifndef BTREE_H
#define BTREE_H

#include "BTreeNode.h"

class BTree {
public:

	fs::path directory; //folder name
	string rootPath;
	int m; //m way
	string nullNode; //nullNode.txt for nullptrs
	int numNodes; //this is for file naming where the nth new node is "node-n.txt"


	BTree(fs::path dir, int m) : m(m), numNodes(0) {
		this->directory = dir;
		if (!fs::exists(directory))
			fs::create_directories(directory);
		//make null node
		nullNode = "nullNode.txt";
		fs::path filePath = directory / nullNode.c_str();
		fstream nullFile;
		nullFile.open(filePath);
		BTreeNode* null = new BTreeNode(directory, m); //null node
		null->writeNode(nullNode);
		nullFile.close();
		delete null;
		rootPath = nullNode; //empty tree
	}

	//insert
	void insertKey(int newKey, string record) { //starting
		if (rootPath == nullNode) { //empty tree
			BTreeNode* root = new BTreeNode(directory, m);
			rootPath = generateFileName(numNodes);
			this->numNodes++;
			root->insert(newKey, record);
			root->writeNode(rootPath);
			delete root;
		}
		else {
			BTreeNode* root = new BTreeNode(directory, m);
			root->readNode(rootPath);
			if (root->search(newKey) != -1) { //duplicate in root
				root->insert(newKey, record);
				root->writeNode(rootPath);
			}
			else if (root->isLeaf) { //root is leaf
				root->insert(newKey, record);
				root->writeNode(rootPath);
			}
			else {
				int c = 0;
				while (root->keys[c].value < newKey && c < root->numKey) //which child to travserse into
					c++;
				string tchild = root->child[c];
				BTreeNode* child = insert(tchild, newKey, record);
				if (child->isFull()) {
					root->splitChild(rootPath, child, c, numNodes);
				}
				else {
					child->writeNode(root->child[c]);
				}
				delete child;
			}
			//check if root full
			if (root->isFull()) {
				string newRootPath = generateFileName(this->numNodes);
				this->numNodes++;
				//root->parent = newRootPath; //new root is old root parent
				string oldRootPath = rootPath;
				rootPath = newRootPath; //change root path

				BTreeNode* newRoot = new BTreeNode(directory, m);
				newRoot->isLeaf = false;
				newRoot->child[0] = oldRootPath;
				newRoot->splitChild(newRootPath, root, 0, numNodes);
			}
			delete root;
		}
	}
	BTreeNode* insert(string path, int newKey, string record) { //recursive
		BTreeNode* node = new BTreeNode(directory, m);
		node->readNode(path);
		if (node->isLeaf) {
			node->insert(newKey, record);
		}
		else {
			int c = 0;
			while (node->keys[c].value < newKey && c < node->numKey) //which child to travserse into
				c++;
			if (newKey == node->keys[c].value) { //duplciate in node
				node->insert(newKey, record);
				node->writeNode(path);
				return node;
			}
			string tchild = node->child[c];
			BTreeNode* child = insert(tchild, newKey, record);
			//check full
			if (child->isFull()) {
				node->splitChild(path, child, c, numNodes);
			}
			else {
				child->writeNode(node->child[c]);
			}
			delete child;
		}
		return node;
	}

	//deletion
	void deleteKey(int delKey,bool removeAll) {
		if (rootPath == nullNode) //empty tree
			return;
		BTreeNode root(directory, m);
		root.readNode(rootPath);
		root.removeNode(rootPath, delKey, removeAll);

		if (root.numKey == 0) { //if empty root
			string oldRoot = rootPath;
			rootPath = root.child[0]; //make root
			BTreeNode* newRoot = new BTreeNode(directory, m);
			newRoot->readNode(root.child[0]);
			newRoot->parent = nullNode;
			newRoot->writeNode(root.child[0]);
			fs::path filePath = directory / oldRoot.c_str();
			fs::remove(filePath);
		}
	}

	//searching
	bool searchKey(int key) {
		BTreeNode* currNode = new BTreeNode(directory, m);
		currNode->readNode(rootPath);
		while (currNode->search(key) == -1) {
			int c = 0;
			if (currNode->isLeaf) {
				delete currNode;
				return false;
			}
			while (currNode->keys[c].value < key && c < currNode->numKey)
				c++;
			string next = currNode->child[c];
			delete currNode;
			currNode = new BTreeNode(directory, m);
			currNode->readNode(next);
		}
		int index = currNode->search(key);
		for (int i = 0;i < currNode->keys->duplicates.size;i++)
			cout << currNode->keys->duplicates[i] << endl;
		delete currNode;
		return true;
	}
};

#endif
