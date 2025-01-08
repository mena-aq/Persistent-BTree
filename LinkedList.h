
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <typename T>
struct ListNode {

	T data;
	ListNode* next;

	ListNode() : next(nullptr) {}
	ListNode(T data) :data(data), next(nullptr) {};

};

template <typename T>
class LinkedList {
public:
	ListNode<T>* head;
	int size;

	LinkedList() :head(nullptr), size(0) {}

	void insert(T data) {
		ListNode<T>* newNode = new ListNode<T>(data);
		newNode->next = head;
		head = newNode;
		size++;
	}
	void remove() { //remove head
		if (head == nullptr)
			return;
		ListNode<T>* del = head;
		head = head->next;
		delete del;
		size--;
	}
	T operator[](int i) {
		int index = 0;
		ListNode<T>* curr = head;
		while (curr && index < i) {
			curr = curr->next;
			index++;
		}
		if (curr)
			return curr->data;
		else
			return T();
	}
	void clearList() {

		ListNode<T>* curr = head;
		while (curr) {
			ListNode<T>* tmp = curr;
			curr = curr->next;
			delete tmp;
		}

		head = nullptr;
		size = 0;

	}
	~LinkedList() {
		ListNode<T>* curr = head;
		while (curr) {
			ListNode<T>* tmp = curr;
			curr = curr->next;
			delete tmp;
		}
	}
};

#endif
