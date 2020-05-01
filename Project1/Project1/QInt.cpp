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

// Ham chuyen mot ki tu so thap luc phan thanh ki tu thap phan
string charHexToDec(char hex) {
	string result;
	if (hex >= '0' && hex <= '9') {
		result.push_back(hex);
		return result;
	}
	if (hex >= 'A' && hex <= 'F') {
		result.push_back('1');
		result.push_back(hex - 'A' + '0');
		return result;
	}
	return result;
}

// Ham lap day mot so nhi phan cho du bo cac 4 bit 
string fill0ToBin(string bin) {
	string result = bin;
	int remainBit = ((bin.size() / 4) + 1) * 4 - bin.size();
	for (int i = 0; i < remainBit; i++) {
		result.insert(bin.begin(), '0');
	}
	return result;
}

// Ham chuyen mot chuoi so thap phan thanh day nhi phan bu 2
string strDecToBin(string dec) {
	string result = {};
	string temp = dec;
	int numlen = dec.size();

	while (numlen > 1 || temp[0] >= 1) {
		if (temp[numlen - 1] % 2 == 1) {
			result.insert(result.begin(), '1');
		}
		else {
			result.insert(result.begin(), '0');
		}
		temp = div2Dec(temp);
		numlen = temp.size();
	}

	return result;
}

// Ham chuyen mot chuoi so thap luc phan thanh thap phan
string strHexToBin(string hex) {
	// Ki tu dau tien trong chuoi thap luc phan khong can phai chuyen thanh bo 4 bit nhi phan
	string result = strDecToBin(charHexToDec(hex[0]));

	// Dau tien la chuyen tung ki tu thap luc phan thanh thap phan, roi chuyen thap phan sang cac bo 4 bit nhi phan
	for (int i = 1; i < hex.size(); i++) {
		string decStr = charHexToDec(hex[i]);
		result = result + fill0ToBin(strDecToBin(decStr));
	}

	return result;
}

// Ham nhap mot chuoi so nhi phan thanh so QInt
QInt binToQInt(string bin) {
	QInt result;

	for (int i = 0; i < bin.size(); i++) {
		if (bin[bin.size() - 1 - i] == '1') {
			setBit1(result.data[i / 32], i % 32);
		}
	}
	result.binLen = bin.size();

	return result;
}

void ScanQInt(istream& in, QInt& x, int base) {
	string temp;
	in >> temp;
	int numlen = temp.size();

	switch (base) {
	case 2: {
		/*for (int i = 0; i < numlen; i++) {
			if (temp[numlen - 1 - i] == '1') {
				setBit1(x.data[i / 32], i % 32);
			}
		}
		x.binLen = numlen;
		break;*/
		x = binToQInt(temp);
		break;
	}
	case 10: {
		/*while (numlen > 1 || temp[0] >= 1) {
			if (temp[numlen - 1] % 2 == 1) {
				setBit1(x.data[x.binLen / 32], x.binLen % 32);
				x.binLen++;
			}
			else {
				x.binLen++;
			}
			temp = div2Dec(temp);
			numlen = temp.size();
		}*/
		x = binToQInt(strDecToBin(temp));
		break;
	}
	case 16: {
		x = binToQInt(strHexToBin(temp));
		break;
	}
	}
}

void PrintQInt(std::ostream& out, QInt x, int base) {
	string result;

	switch (base) {
	case 2: {
		for (int i = 0; i < x.binLen; i++) {
			result.push_back(getBit(x.data[i / 32], i % 32));
		}
		break;
	}
	case 10: {
		break;
	}
	}

	out << result;
}

bool* DecToBin(QInt x) {
	bool* result = new bool[x.binLen];
	for (int i = 0; i < x.binLen; i++) {
		
	}
	return nullptr;
}

void main() {
	QInt x;
	ScanQInt(cin, x, 10);

}