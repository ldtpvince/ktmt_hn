#include "Qfloat.h"
#include <iostream>

//bias 15 bit
const unsigned int bias = 16383;
//day bit 01111111111111110000000000000000 khong dau
const unsigned int layMu = 2147418112;
//day bit 00000000000000001111111111111111 khong dau
const unsigned int layTri = 65535;		
//Chia chuoi so nguyen duong cho 2
string strDecDiv2(string s) {
	string res;
	int temp = 0;
	for (int i = 0; i < s.length(); i++) {
		temp = temp * 10 + (s[i] - '0');
		if (i > 0 || (i == 0 & temp > 1))
			res.push_back((temp / 2) + '0');
		temp %= 2;
	}
	return res;
}

//Chuyen chuoi so nguyen duong thanh chuoi nhi phan
string strDecToStrBin(string s) {
	string res;
	while (s != "") {
		res.push_back((s[s.length() - 1] - '0') % 2 + '0');
		s = strDecDiv2(s);
	}
	reverse(res.begin(), res.end());
	return res;
}
//Chuyen doi so thap phan thanh chuoi nhi phan 15 bit
string decToStrBin(int dec) {
	string res;
	while (dec != 1) {
		res.push_back((dec % 2) + '0');
		dec /= 2;
	}
	res.push_back('1');
	while (res.length() < 15)
		res.push_back('0');
	reverse(res.begin(), res.end());
	return res;
}

//Nhan so thuc 0.s voi 2, lay phan nguyen
bool layBit(string& s) {
	bool temp = 0;
	string sClone;
	for (int i = s.length() - 1; i >= 0; i--) {
		int kq = (s[i] - '0') * 2 + temp;
		sClone.push_back(kq % 10);
		temp = kq / 10;
	}
	return (temp == 1);
}

//Chuyen chuoi 32 bit thanh so nguyen khong dau
unsigned int strBinToDec(string s) {
	unsigned int res = 0;
	int temp = 1;
	for (int i = 0; i < s.length(); i--)
		res = res * 2 + (s[i] - '0');
	return res;
}

//Khoi tao khong tham so
Qfloat::Qfloat() {
	unsigned int other[4] = { 0 };
	this->updateData(other);
}

//Khoi tao tu chuoi so thuc
Qfloat::Qfloat(string s) {
	string res;
	if (s[0] == '-') {
		res = "1";
		s.erase(0, 1);
	}
	else
		res = "0";
	while (s[s[0]] == '0')
		s.erase(0, 1);
	while (s[s.length() - 1] == '0')
		s.erase(s.length() - 1, 1);
	int pos = s.find('.');
	string temp = strDecToStrBin(s.substr(0, pos));
	if (temp == "")
		res += "111111111111111"; 
	else {
		int exponent = bias + temp.length() - 1;
		res += decToStrBin(exponent);
	}
	//Can cap nhat error
	res += temp;
	temp = s.substr(pos + 1, s.length() - pos);
	while (res.length() < 128)
		res.push_back(layBit(s));
	*this = res;
}

//Sao chep du lieu vao data
void Qfloat::updateData(unsigned int other[4]) {
	for (int i = 0; i < 4; i++)
		this->data[i] = other[i];
}

//Kiem tra phan tri bang 0
bool Qfloat::checkSignificandEqualZero() {
	bool res = true;
	for (int i = 0; i < 3; i++)
		res = res && (this->data[i] == 0);
	res = res && ((this->data[3] & layTri) == 0);
	return res;
}

//Toan tu gan: Qfloat = string
Qfloat& Qfloat::operator =(string s) {
	Qfloat res = s;
	for (int i = 0; i < 4; i++)
		res.data[i] = strBinToDec(s.substr(32 * i, 32));
	return res;
}

//Nhap so thuc
void Qfloat::ScanQfloat(Qfloat& x) {
	string s;
	getline(cin, s);
	Qfloat temp = s;
	x = s;
}

//Xuat so thuc
void Qfloat::PrintQfloat(Qfloat x) {
	unsigned int mu = x.data[3] & layMu;
	switch (mu)
	{
	case 0: //day 15 bit toan 0
		if (x.checkSignificandEqualZero()) {
			cout << 0;
			return;
		}
		else {
			cout << "So dang khong chuan";
			return;
		}
	case 32767: //day 15 bit toan 1
		if (x.checkSignificandEqualZero()) {
			cout << 0;
		}
	default:
		cout << "So dang chuan";
		break;
	}
}

//Chuyen doi Qfloat nhi phan sang thap phan
Qfloat Qfloat::BinToDec(string bit) {
	Qfloat res;
	unsigned int temp[4];
	for (int i = 0; i < 4; i++)
		temp[i] = strBinToDec(bit.substr(32 * i, 32));
	res.updateData(temp);
	return res;
}

//Chuyen doi Qfloat thap phan sang nhi phan
string Qfloat::DecToBin(Qfloat x) {
	string res;
	for (int i = 3; i >= 0; i++)
		res += decToStrBin(this->data[i]);
	return res;
}