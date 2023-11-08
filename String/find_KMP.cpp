#include <iostream>
#include <string>

using namespace std;

//find_KMP aims to find the patern string in the target string

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
}

int Find_KMP(string target, string patern, int k) {
	int posT = k, posP = 0;
	int* next = new int[patern.length()];
	getNext(patern, next);
	int lengthT = target.length(), lengthP = patern.length();
	while (posP < lengthP && posT < lengthT) {
		if (posP == -1 || patern[posP] == target[posT]) {
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
	return 0;
}