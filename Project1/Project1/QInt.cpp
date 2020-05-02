#include "QInt.h"
using namespace std;

QInt::QInt() {
	for (int i = 0; i < 4; i++) {
		data[i] = 0;
	}
	binLen = 0;
}

bool isNegativeDec(string& dec) {
	if (dec[0] == '-') {
		dec.erase(0, 1);
		return true;
	}
	return false;
}

bool isNegativeBin(string bin) {
	if (bin[0] == '1') {
		return true;
	}
	return false;
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
			result.push_back(temp / 2 + '0');
			temp = temp % 2;
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

// ------------------------------------------------------Ham scan----------------------------------------------------

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
	bool negativeFlag = isNegativeDec(dec);
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

	if (negativeFlag) { 
		bool first1Bit = false;
		for (int i = result.size() - 1; i >= 0; i--) {
			if (result[i] == '1' && !first1Bit) {
				first1Bit = true;
				continue;
			}
			if (first1Bit) {
				result[i] = ~((result[i] - '0') | 0) + '0';
			}
		}
		for (int i = 128 - result.size(); i > 0; i--) {
			result.insert(result.begin(), '1');
		}
	}

	return result;
}

// Ham chuyen mot chuoi so thap luc phan thanh nhi phan bu 2
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

	for (int i = bin.size() - 1 ; i  >= 0; i--) {
		if (bin[i] == '1') {
			setBit1(result.data[3 - (bin.size() - i - 1) / 32], 31 - bin.size() + 1 + i);
		}
	}
	result.binLen = bin.size();

	return result;
}

// Ham nhap mot chuoi so va luu vao QInt voi co so tuong ung
void ScanQInt(istream& in, QInt& x, int base) {
	string temp;
	in >> temp;
	int numlen = temp.size();

	switch (base) {
	case 2: {
		x = binToQInt(temp);
		break;
	}
	case 10: {
		x = binToQInt(strDecToBin(temp));
		break;
	}
	case 16: {
		x = binToQInt(strHexToBin(temp));
		break;
	}
	}
}

// ------------------------------------------------------Ham print----------------------------------------------------

string QInt::QIntToBin() {
	string result;
	for (int i = 0; i < binLen; i++) {

	}
}
// Gom 3 ham chuyen tu QInt -> string nhi phan -> chuyen qua cac co so khac nhu thap phan hay thap luc phan
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

void main() {
	QInt x;
	ScanQInt(cin, x, 10);

}