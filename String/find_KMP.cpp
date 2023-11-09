#include <iostream>
#include <string>

using namespace std;

//find_KMP aims to find the pattern string in the target string

void getNext(string str, int* next) {
	int j = 0, k = -1, length = str.length();
	next[0] = -1;
	while (j < length) {
		if (k == -1 || str[j] == str[k]) {
			j++;
			k++;
			next[j] = k;
		}
		else
			k = next[k];
	}
	for (int i = 0; i < length; i++)
		cout << next[i] << " ";
	cout << endl;
}

int Find_KMP(string target, string pattern, int k) {//find pattern in the target from the kth char
	int posT = k, posP = 0;
	int* next = new int[pattern.length()];
	getNext(pattern, next);
	int lengthT = target.length(), lengthP = pattern.length();
	while (posP < lengthP && posT < lengthT) {
		if (posP == -1 || pattern[posP] == target[posT]) {
			posP++;
			posT++;
		}
		else
			posP = next[posP];
	}
	if (posP < lengthP)
		return -1;
	else
		return posT - lengthP;
}

int main() {
	string tar, pat;
	cin >> tar >> pat;
	int pos = Find_KMP(tar, pat, 0);
	cout << pos;
	return 0;
}