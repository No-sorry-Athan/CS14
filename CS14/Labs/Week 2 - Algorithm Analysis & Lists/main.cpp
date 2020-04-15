#include "IntList.h"

using namespace std;

int main() {
	IntList list;
	cout << "Empty: " << boolalpha << list.empty() << endl;
	cout << "Pushback: 3, 4, 5, 6" << endl;
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);
	list.push_back(6);
	cout << "Empty: " << boolalpha << list.empty() << endl;
	cout << list << endl;
	cout << "Pushfront: 2, 1 -1" << endl;
	list.push_front(2);
	list.push_front(1);
	list.push_front(-1);
	cout << list << endl;

	cout << "Popfront and back" << endl;
	list.pop_back();
	list.pop_front();
	cout << list << endl;

	cout << "Reverse" << endl;
	list.printReverse();

	list.pop_front();
	list.pop_front();
	list.pop_front();
	list.pop_front();
	list.pop_front();
	list.pop_front();
	cout << list << endl;
	list.printReverse();

	cout << "Empty: " << boolalpha << list.empty() << endl;
	list.pop_back();

	IntList* list2 = new IntList();
	for (int i = 0; i < 10; i++) {
		list2->push_back(i);
	}

	cout << "List2:" << *list2 << endl;
	delete list2;
	//cout << *list2 << endl;


	return 0;
}