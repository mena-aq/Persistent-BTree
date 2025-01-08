#ifndef KEY_H
#define KEY_H

#include "LinkedList.h"
//#include "Record.h"
//#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct Key {

	int value;

	LinkedList<string> duplicates;
	Key() :value(-1) {}
	Key(int value) :value(value) {}

	Key(const Key& copy) {
		duplicates.clearList();
		this->value = copy.value;
		ListNode<string>* otherN = copy.duplicates.head;
		while (otherN) {  //deep copy
			this->duplicates.insert(otherN->data);
			otherN = otherN->next;
		}
	}

	void operator=(const Key& other) {
		this->duplicates.clearList();
		this->value = other.value;
		ListNode<string>* otherN = other.duplicates.head;
		while (otherN) {  //deep copy
			this->duplicates.insert(otherN->data);
			otherN = otherN->next;
		}
	}
	void clearKey() {
		value = -1;
		duplicates.clearList();
	}
	void insertDuplicates(string record) {
		duplicates.insert(record);
	}
	bool operator==(const Key& other) {
		return (this->value == other.value);
	}
	~Key() {
		if (this->duplicates.head != nullptr)
			this->duplicates.clearList();
	}
};

ostream& operator<<(ostream& output, Key& key) {
	cout << key.value;
	return output;
}

#endif
