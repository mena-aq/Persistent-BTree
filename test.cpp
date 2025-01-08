#include "BTree.h"

int main() {

	////// a test file to show functionality

	// creating node files in MyBTree/
	const string folder = "MyBTree";

	int m = 5;

	BTree btree(folder,m); //create a BTree with maximum degree m=3

	//insert keys and corresponding records in string format into the tree
	btree.insertKey(12, "record12a");
	btree.insertKey(32, "record32");
	btree.insertKey(54, "record54");
	btree.insertKey(65, "record65");
	btree.insertKey(74, "record74a");
	btree.insertKey(74, "record74b");
	btree.insertKey(23, "record23");
	btree.insertKey(12, "record12b");

	//to search for a key and print the corresponding records onto the console
	btree.searchKey(12);

	//to delete a key
	const bool removeAll = true; //true to remove all record instances 
	const bool removeOne = false; //false to remove the latest one only

	btree.deleteKey(12, removeAll);
	btree.deleteKey(32, removeAll);
	btree.deleteKey(74, removeOne);


	return 0;
}