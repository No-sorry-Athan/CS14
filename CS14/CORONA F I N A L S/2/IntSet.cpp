#include "IntSet.h"

ostream& operator<<(ostream& os, IntSet& iSet) {
	os << "Unique Students: " << iSet.size() << endl;
	os << "\tComparisons made: " << iSet.comparisons() << endl;
	return os;
}

IntSet::IntSet() :_capacity(1){
	_comparisons = 0;
	_size = 0;
	_table = new setRecord[_capacity];
}

IntSet::IntSet(const IntSet& iSet) :_capacity(iSet._capacity){
	_comparisons = iSet._comparisons;
	_size = iSet.size();
	 _table = new setRecord[_capacity];
	for (int i = 0; i < _capacity; i++) {
		if (iSet._table[i].status == Occupied) {
			insert(iSet._table[i].value);
			_table[i].status = iSet._table[i].status;
		}
	}
}

IntSet::IntSet(int n) : _capacity(n){
	_comparisons = 0;
	_size = 0;
	_table = new setRecord[_capacity];
}

IntSet& IntSet::operator=(const IntSet& copy) {
	if (this != &copy) {
		delete[] _table;

		_comparisons = copy._comparisons;
		_capacity = copy.capacity();
		_size = copy.size();
		for (int i = 0; i < _capacity; i++) {
			if (copy._table[i].status == Occupied) {
				insert(copy._table[i].value);
				_table[i].status = copy._table[i].status;
			}
		}
	}
	return *this;
}

void IntSet::erase(int val) {
	if (count(val) == 0)
		return;
	_comparisons++;

	int index = findIndex(val);
	_table[hash(index)].status = Empty;

}

void IntSet::insert(int val) {
	if (count(val) == 1) 
		return;
	else if (_size + 1 >= _capacity* ((double)2 / 3))
		rehash(_capacity * 3);
	_comparisons++;

	
	int bread = probe(val);
	_table[bread].status = Occupied;
	_table[bread].value = val;
	_size++;
	
	

}

void IntSet::rehash(size_t val) {
	_comparisons++;
	setRecord* temp = new setRecord[val];
	for (int i = 0; i < _capacity; i++) {
		int vallululul = _table[i].value;
		if (_table[i].status == Occupied) {
			temp[probe(vallululul)].status = _table[i].status;
			temp[probe(vallululul)].value = _table[i].value;
		}
	}
	delete[] _table;
	_table = temp;
	_capacity = val;
}

int IntSet::comparisons() {
	return _comparisons;
}

int IntSet::findIndex(int val) {
	for (int i = hash(val); _table[i].status != Empty_since_start; i = (i+1)%_capacity) {
		if (_table[i].value == val && _table[i].status == Occupied)
			return i;
	}
	return -1;
}

size_t IntSet::size() const {
	return this->_size;
}

size_t IntSet::capacity() const {
	return this->_capacity;
}

bool IntSet::empty() const {
	return this->_size == 0;
}

int IntSet::count(int val) {
	for (int i = hash(val); _table[i].value != Empty_since_start; i = (i+1)%_capacity) {
		_comparisons++;
		if (_table[i].status == val && _table[i].status != Empty) {
			return 1;
		}
	}

	return 0;
}


int IntSet::probe(int val) const {
	int i = hash(val);
	for (i; _table[i].status != Empty_since_start; i = (i + 1) % _capacity) {
		if (_table[i].value == val ) {
			return i;
		}
	}
	return i;
}

int IntSet::hash(int val1, int val2) const {
	string s = to_string(val1);
	s = s.substr(s.size() - 3, s.size());
	int num = atoi(s.c_str());
	return num % _capacity;
}

int IntSet::hash_map(int val) const {
	return 1;
}

int IntSet::compression_map(int val) const {
	return hash(val) % _capacity;
}


