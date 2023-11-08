#include <iostream>
#include <cassert>
#include <vector>
#define DEFAULTSIZE 100

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
//friend istream& operator>>(istream& is, SparseMatrix& M);
public:
    SparseMatrix(int maxsize = 100);
    ~SparseMatrix() {}
    void input(vector<vector<int> > elements);
    void Transpose(SparseMatrix& other);
    void Add(SparseMatrix& other, SparseMatrix& answer);
    void Multiply(SparseMatrix& other, SparseMatrix& answer);
private:
    int rows, cols, terms;
    vector<Trituple> elem;
    int maxterms;
};

ostream& operator<<(ostream& os, SparseMatrix& M) {
    os << "rows = " << M.rows << endl;
    os << "cols = " << M.cols << endl;
    os << "Nonzero terms = " << M.terms << endl;
    for (int i = 0; i < M.terms; i++) {
        os << "M[" << M.elem[i].row << "][" << M.elem[i].col << "]=" << M.elem[i].value << endl;
    }
    return os;
}

/*istream& operator>>(istream& is, SparseMatrix& M) {
    cout << "请输入矩阵的行数，列数：" << endl;
    is >> M.rows >> M.cols;
    Trituple temp;
    int endTag = -1;
    M.terms = 0;
    cout << "请输入元素行号，列号和值：" << endl;
    is >> temp.row >> temp.col >> temp.value;
    while (temp.row != endTag) {
        M.Insert(temp);
        cout << "请输入元素行号，列号和值：" << endl;
        is >> temp.row >> temp.col >> temp.value;
    }
    return is;
}*/

SparseMatrix::SparseMatrix(int maxsize) {
    elem.reserve(maxsize);
    rows = cols = terms = 0;
}

void SparseMatrix::input(vector<vector<int> > elements) {
    Trituple temp;
    rows = elements[0][0];
    cols = elements[0][1];
    terms = elements[0][2];
    for (int i = 1; i < elements.size(); i++) {
        temp.row = elements[i][0];
        temp.col = elements[i][1];
        temp.value = elements[i][2];
        elem.push_back(temp);
    }
}

void SparseMatrix::Transpose(SparseMatrix& other) {

}

int main() {
    vector<vector<int> > input = {{6, 7, 9}, 
                                  {0, 2, 2}, {1, 0, 3}, {1, 3, -11}, 
                                  {2, 3, -6}, {3, 5, -17}, {4, 1, 9}, 
                                  {4, 4, 19}, {5, 3, 8}, {5, 6, -52}};
    SparseMatrix Matrix(100);
    Matrix.input(input);
    cout << Matrix;
    return 0;
}