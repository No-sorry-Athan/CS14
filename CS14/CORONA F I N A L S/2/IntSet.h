#ifndef __INTSET_H_
#define __INTSET_H_

#include <fstream>
#include <string>
using namespace std;
class IntSet {
    enum Status { Empty_since_start, Empty, Occupied };

    struct setRecord {
        int value;
        Status status = Empty_since_start; 
    };

    friend std::ostream& operator<<(std::ostream&,const IntSet&);
    private:
        int _comparisons = 0;
        size_t _size = 0;
        size_t _capacity;
        setRecord *_table;

    public:
        IntSet();
        explicit IntSet(int n);
        IntSet(const IntSet &);
        ~IntSet() { delete[] _table; }
        IntSet &operator=(const IntSet &copy);

        void insert(int);
        void erase(int);
        void rehash(size_t);

        int comparisons();
        size_t size() const;
        size_t capacity() const;
        bool empty() const;
        int count(int); 

    private:
        int findIndex(int);
        int probe(int) const;
        int hash(int,int=0) const;
        int hash_map(int) const;
        int compression_map(int) const;
};

#endif // __INTSET_H_
