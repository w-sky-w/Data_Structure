#include <iostream>
#include <cassert>

using namespace std;

struct Trituple {
    int row, col;
    int value;
    Trituple& operator=(Trituple& other) {
        row = other.row;
        col = other.col;
        value = other.value;
        return *this;
    }
};

class SparseMatrix {
friend ostream& operator<<(ostream& os, SparseMatrix& M);
friend istream& operator>>(istream& is, SparseMatrix& M);
public:
    SparseMatrix(int maxsize = 100);
    ~SparseMatrix() {delete []elem;}
    void Transpose(SparseMatrix& other);
    void Add(SparseMatrix& other, SparseMatrix& answer);
    void Multiply(SparseMatrix& other, SparseMatrix& answer);
private:
    int rows, cols, terms;
    Trituple* elem;
    int maxterms;
};

SparseMatrix::SparseMatrix(int maxsize) {
    elem = new Trituple[maxsize];
    assert(elem != nullptr);
    rows = cols = terms = 0;
}