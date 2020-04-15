#include "IntList.h"

IntList::IntList() {
	dummyHead = new IntNode(-1);
	dummyTail = new IntNode(-1);
	dummyHead->next = dummyTail;
	dummyHead->prev = nullptr;
	dummyTail->prev = dummyHead;
	dummyTail->next = nullptr;
}

IntList::~IntList() {
	while (!empty()) {
		pop_front();
	}
	delete dummyHead;
	delete dummyTail;
}

void IntList::push_front(int val) {
	IntNode* node = new IntNode(val);
	node->next = dummyHead->next;
	node->prev = dummyHead;
	dummyHead->next->prev = node;
	dummyHead->next = node;
}

void IntList::push_back(int val) {
	IntNode* node = new IntNode(val);
	node->prev = dummyTail->prev;
	node->next = dummyTail;
	dummyTail->prev->next = node;
	dummyTail->prev = node;
}

void IntList::pop_front() {
	if (empty()) {
		return;
	}
	else {
		IntNode* next = dummyHead->next->next;
		next->prev = dummyHead;
		delete dummyHead->next;
		dummyHead->next = next;
	}
}

void IntList::pop_back() {
	if (empty()) {
		return;
	}
	else {
		IntNode* prior = dummyTail->prev->prev;
		prior->next = dummyTail;
		delete dummyTail->prev;
		dummyTail->prev = prior;
	}

}

bool IntList::empty() const {
	return (dummyHead->next == dummyTail && dummyTail->prev == dummyHead);

	//log if both sides
	//if 
}

void IntList::printReverse()const {
	if (empty()) {
		return;
	}
	else {
		IntNode* ehh = dummyTail->prev;
		while (ehh != dummyHead) {
			cout << ehh->data;
			if (ehh->prev != dummyHead) {
				cout << " ";
			}
			ehh = ehh->prev;
		}
	}
}

ostream& operator<<(ostream& os, const IntList& rhs) {
	if (rhs.empty()) {
		return os;
	}

	IntNode* bread = rhs.dummyHead->next;
	while (bread != rhs.dummyTail) {
		if (bread->next == rhs.dummyTail) {
			os << bread->data;
		}
		else {
			os << bread->data << " ";
		}
		bread = bread->next;
	}
	return os;
}

