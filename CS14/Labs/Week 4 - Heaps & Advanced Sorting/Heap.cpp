#include "Heap.h"

Heap::Heap() {
	for (int i = 0; i < MAX_HEAP_SIZE; i++) {
		arr[i] = nullptr;
	}
	numItems = 0;
}

void Heap::enqueue(PrintJob* j) {
	if (!full()) {
		if (empty()) {
			numItems++;
			arr[0] = j;
		}
		else {
			int x = numItems;
			while (x > 0 && arr[(x - 1) / 2]->getPriority() < j->getPriority()) {
				arr[x] = arr[(x - 1) / 2];
				x = (x - 1) / 2;
			}
			arr[x] = j;
			numItems++;
		}
	}
}

void Heap::dequeue() {
	if (empty()) {
		cout << "Error: Tried to dequeue an empty heap" << endl;
	}
	else {
		swap(arr[0], arr[numItems - 1]);
		arr[numItems - 1] = nullptr;
		numItems--;
		//print();
		PrintJob* left = getLeft(0);
		PrintJob* right = getRight(0);
		if (left && right) {
			if ((arr[0]->getPriority() > getLeft(0)->getPriority()) && (arr[0]->getPriority() > getRight(0)->getPriority())) {
				return;
			}
			else {
				trickleDown(0);
			}
		}
		else if (!left && right) {
			if (arr[0]->getPriority() > getRight(0)->getPriority())
				return;
			else {
				trickleDown(0);
			}
		}
		else if (left && !right) {
			if (arr[0]->getPriority() > getLeft(0)->getPriority())
				return;
			else {
				trickleDown(0);
			}
		}
		else {
			return;
		}
	}
}

PrintJob* Heap::highest() {
	if (!empty())
		return arr[0];
	else
		return nullptr;
}

void Heap::print() {
	if (!empty()) {
		PrintJob* job = arr[0];
		cout << "Priority: " << job->getPriority() << ", Job Number: " << job->getJobNumber() << ", Number of Pages: " << job->getPages() << endl;

		/*for (int i = 0; i < numItems; i++) {
			PrintJob* job = arr[i];
			cout << "Priority: " << job->getPriority() << ", Job Number: " << job->getJobNumber() << ", Number of Pages: " << job->getPages() << endl;
		}*/
	}
	else {
		cout << "Error: Print called on empty heap" << endl;
	}
}

void Heap::trickleDown(int loca) {
	PrintJob* left= getLeft(loca);
	PrintJob* right = getRight(loca);
	int ind;
	if (left != nullptr && right != nullptr) {
		if (left->getPriority() > right->getPriority()) {
			ind = (2 * loca) + 1;
			swap(arr[loca], arr[ind]);
			if (hasChildren(ind)) {
				trickleDown(ind);
			}
			else return;
		}
		else if (right->getPriority() > left->getPriority()) {
			ind = (2 * loca) + 2;
			swap(arr[loca], arr[ind]);
			if (hasChildren(ind)) {
				trickleDown(ind);
			}
			else return;
		}
	}
	else if (!left && right) {
		ind = (2 * loca) + 2;
		swap(arr[loca], arr[ind]);
		if (hasChildren(ind)) {
			trickleDown(ind);
		}
		else return;
	}
	else if (left && !right) {
		ind = (2 * loca) + 1;
		swap(arr[loca], arr[ind]);
		if (hasChildren(ind)) {
			trickleDown(ind);
		}
		else return;
	}	
}

PrintJob* Heap::getLeft(int index) {
	if ((2 * index) + 1 > numItems)
		return nullptr;
	return arr[(2 * index) + 1];
}

PrintJob* Heap::getRight(int index) {
	if ((2 * index) + 2 > numItems)
		return nullptr;
	return arr[(2 * index) + 2];
}

PrintJob* Heap::getParent(int index) {
	return arr[(index - 1) / 2];
}

bool Heap::hasChildren(int index) {
	return (getLeft(index) || getRight(index));
}



bool Heap::empty() {
	return numItems == 0;
}

bool Heap::full() {
	return numItems == MAX_HEAP_SIZE;
}