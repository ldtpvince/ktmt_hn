#include <iostream>
#include <string>
#include "QInt.h"
using namespace std;

string div2Dec(string src) {
	string result;
	int temp = 0;

	for (int i = 0; i < src.size(); i++) {
		if (src[i] >= '2') {
			temp = temp * 10 + src[i] - '0';
			result.push_back(temp / 2 + '0');
			temp = src[i] % 2;
			continue;
		}
		if (src[i] < '2' && i > 0) {
			temp = temp * 10 + src[i] - '0';
			result.push_back('0');
		}
		else {
			temp = temp * 10 + src[i] - '0';
		}
	}

	return result;
}

int QInt::setBit(int& data, int offset) {
	return (data | (1 << (31 - offset)));
}

int QInt::getBit(int data, int offset) {
	return (data >> (31 - offset) & 1);
}

void ScanQInt(QInt& x) {
	string temp;
	getline(cin, temp);
	int numlen = temp.size();

	while (numlen > 1) {
		
	}
}

void main() {
	cout << div2Dec("4");
}