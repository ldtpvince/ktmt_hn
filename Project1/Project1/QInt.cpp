#include <iostream>
#include <istream>
#include <string>
#include "QInt.h"
using namespace std;

QInt::QInt() {
	for (int i = 0; i < 4; i++) {
		data[i] = 0;
	}
	binLen = 0;
}

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

int setBit1(int& data, int offset) {
	data = (data | (1 << (31 - offset)));
	return 0;
}

int getBit(int data, int offset) {
	return (data >> (31 - offset) & 1);
}

void ScanQInt(istream& in, QInt& x, int base) {
	string temp;
	in >> temp;
	int numlen = temp.size();

	switch (base) {
	case 2: {
		for (int i = 0; i < numlen; i++) {
			if (temp[numlen - 1 - i] == '1') {
				setBit1(x.data[i / 32], i % 32);
			}
		}
		x.binLen = numlen;
		break;
	}
	case 10: {
		while (numlen > 1 || temp[0] >= 1) {
			if (temp[numlen - 1] % 2 == 1) {
				setBit1(x.data[x.binLen / 32], x.binLen % 32);
				x.binLen++;
			}
			else {
				x.binLen++;
			}
			temp = div2Dec(temp);
			numlen = temp.size();
		}
		break;
	}
	}

	
}

bool* DecToBin(QInt x) {
	bool* result = new bool[x.binLen];
	for (int i = 0; i < x.binLen; i++) {
		
	}
	return nullptr;
}

void PrintQBit(QInt x) {
	string result;


}

void main() {
	QInt x;
	ScanQInt(cin, x, 2);

}