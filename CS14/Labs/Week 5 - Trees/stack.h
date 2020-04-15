#ifndef STACK_H
#include <stdexcept>
#define STACK_H	
#define MAX_SIZE 20

using namespace std;

template<typename T>
class stack {
private:
	int size;
	T data[MAX_SIZE];
public:
	stack<T>() {
		size = 0;
	}

	void push(T val) {
		if (size >= MAX_SIZE) {
			throw overflow_error("Called push on full stack.");
		}
		else {
			data[size] = val;
			size++;
		}
	}

	void pop() {
		if (empty()) {
			throw underflow_error("Called pop on empty stack.");
		}
		else {
			size--;
		} 
	}

	T top() const {
		if (empty()) {
			throw underflow_error("Called top on empty stack.");
		}
		else {
			return data[size - 1];
		}
	}

	bool empty() const {
		return size == 0;
	}
};

#endif // !STACK_H
