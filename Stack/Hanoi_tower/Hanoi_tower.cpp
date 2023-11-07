#include <iostream>

using namespace std;

void Hanoi(int n, char A, char B, char C) {
    if (n == 1)//directly move A to C
        cout << "Move top disk from peg " << A << " to peg " << C << endl;
    else {
        Hanoi(n - 1, A, C, B);//move n - 1 disk from A to B through C
        cout << "Move top disk from peg " << A << " to peg " << C << endl;//move the nth disk from A to C
        Hanoi(n - 1, B, A, C);//move n - 1 disk from B to C through A
    }
}

int main() {
    int n = 5;
    Hanoi(n, 'A', 'B', 'C');
}