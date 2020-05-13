#include "Qfloat.h"
#include <iostream>
#include "QInt.h"
#include <sstream>

//bias 15 bit
const unsigned int bias = 16383;
//day bit 01111111111111110000000000000000 khong dau
const unsigned int layMu = 2147418112;
//day bit 00000000000000001111111111111111 khong dau
const unsigned int layTri = 65535;		

//Kiem tra chuoi co toan ky tu da cho khong
bool checkStr(string s, char c) {
	for (int i = 0; i < s.length(); i++)
		if (s[i] != c)
			return false;
	return true;
}

string toStrBias(int exp) {
	exp = exp + MAX_EXP - 1;
	string result = {};
	for (int i = 0; i < BIT_EXP; i++) {
		int bit = (exp >> i) & 1;
		char c = '0' + bit;
		result = c + result;
	}
	return result;
}

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
string toBinExp(int dec) {
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

//Nhan day thap phan voi 2
bool mul2(string& s) {
	bool temp = 0; //Bien nho
	string result;
	for (int i = s.length() - 1; i >= 0; i--) {
		int kq = (s[i] - '0') * 2 + temp;
		result.push_back(kq % 10 + '0');
		temp = kq / 10;
	}
	while (result[0] == '0' && result.length() > 1)
		result.erase(0, 1);
	reverse(result.begin(), result.end());
	s = result;
	return (temp == 1);
}

//Khoi tao khong tham so
Qfloat::Qfloat() {
	for (int i = 0; i < MAX_N; i++)
		this->data[i] = 0;
}

//Chuyen tu chuoi thap phan sang Qfloat
Qfloat strDecToQfloat(string s) {
	Qfloat result;//Khoi tao result=0
	//Xet s = 0
	if (s == "0")
		return result;
	//Xet dau
	if (s[0] == '-') {
		result.setBit(LEN - 1, 1);
		s.erase(0, 1);
	}
	//Xet chuoi nguyen
	if (s.find('.', 0) == string::npos)
		s += ".0";
	//Tach phan nguyen va phan thap phan
	int pos = s.find('.');
	string Int = s.substr(0, pos);
	string Frac = s.substr(pos + 1, s.length() - pos - 1);
	//Chuan hoa
	while (Int.length() > 1 && Int[0] == '0')
		Int.erase(0, 1);
	while (Frac.length() > 1 && Frac[Frac.length() - 1] == '0')
		Frac.erase(Frac.length() - 1, 1);
	string strExp;
	string strSigni;
	//Xet phan nguyen khac 0
	if (Int != "0") {
		//Doi phan nguyen
		QInt temp;
		istringstream istr(Int);
		ScanQInt(istr, temp, 10);
		string binInt = QInt::DecToBin(temp);
		//Lay exp va khoi tao strSigni neu phan nguyen chuyen sang phan tri
		int exp = binInt.length() - 1;
		if (exp > 0)
			strSigni = binInt.substr(1, exp);
		exp += BIAS;
		strExp = toBinExp(exp);
	}
	else {
		int exp = 0;
		while (1) {
			exp--;
			if (mul2(Frac))
				break;
		}
		exp += bias;
		strExp = toBinExp(exp);
	}
	while (strSigni.length() < BIT_SIGN) {
		if (mul2(Frac))
			strSigni += '1';
		else
			strSigni += '0';
		if (checkStr(Frac, '0'))
			break;
	}
	while (strSigni.length() < BIT_SIGN)
		strSigni += '0';
	for (int i = 0; i < BIT_EXP; i++)
		result.setBit(LEN - 2 - i, strExp[i] == '1');
	for (int i = 0; i < BIT_SIGN; i++)
		result.setBit(LEN - 2 - BIT_EXP - i, strSigni[i] == '1');
	return result;
}

//Kiem tra bang 0
bool Qfloat::isZero() const {
	for (int i = 0; i < MAX_N * BIT - 1; i++)
		if (this->getBit(i))
			return false;
	return true;
}

//Lay bit
bool Qfloat::getBit(int index) const {
	return (this->data[MAX_N - 1 - (index / BIT)] >> (index % 32) & 1);
}

//Gan bit
void Qfloat::setBit(int index, bool bit) {
	int i = MAX_N - 1 - (index / BIT);
	int pos = index % 32;
	if (bit)
		this->data[i] = this->data[i] | (1 << pos);
	else
		this->data[i] = this->data[i] & ~(1 << pos);
}

//Lay dau
string Qfloat::getSigni() const {
	string result;
	for (int i = BIT_SIGN - 1; i >= 0; i--) {
		char bit = this->getBit(i) + '0';
		result = result + bit;
	}
	return result;
}

//Lay mu
int Qfloat::getExp()const {
	int result = -((1 << (BIT_EXP - 1)) - 1); //bias
	for (int i = 0; i < BIT_EXP; i++)
		if (this->getBit(MAX_N * BIT - BIT_EXP - 1 + i) == 1)
			result += (1 << i);
	return result;
}

//So vo cung
Qfloat Qfloat::inf(bool sign) {
	Qfloat result;
	result.data[0] = (~(1 << BIT_EXP)) << BIT - BIT_EXP - 1;
	return result;
}

string mulByHalf(string s, bool con)
{
	string result = "";
	int carry = 0;
	for (int i = s.length() - 1; i >= 0; i--) {
		int temp = s[i] - '0';
		temp = temp * 5 + carry;
		result += (temp % 10 + '0');
		carry = temp / 10;
	}
	result += (carry + '0');

	reverse(result.begin(), result.end());
	if (con)
		result[0] = result[0] + 5;

	while (result.length() > 1 && result[result.length() - 1] == '0')
		result.erase(result.length() - 1, 1);
	return result;
}

//Chuyen Qfloat sang chuoi thap phan
string toStrDec(Qfloat x) {
	string result;
	string strBin = Qfloat::DecToBin(x);
	string strExp = strBin.substr(1, 15);
	string strSigni = strBin.substr(16, 112);
	if (strBin[0] == '1')
		result += "-";

	if (checkStr(strExp, '0')) {
		if (checkStr(strSigni, '0'))
			return "0";
		else
			return result + "DENORMALIZED";
	}
	else
		if (checkStr(strExp, '0')) {
			if (checkStr(strSigni, '0'))
				return result + "Inf";
			else
				return "NaN";
		}
	int exp = stoi(strExp, nullptr, 2);
	exp -= bias;

	//Tim phan nguyen, thap phan o he nhi phan
	string strInt = "1";
	string strFrac = strSigni;
	while (exp != 0) {
		if (exp < 0) {
			strFrac = strInt[strInt.length() - 1] + strFrac;
			strInt.erase(strInt.length() - 1, 1);
			strInt = '0' + strInt;
			exp++;
		}
		else {
			strInt += strFrac[0];
			strFrac.erase(0, 1);
			strFrac += '0';
			exp--;
		}
	}

	while (strInt.length() > 1 && strInt[0] == '0')
		strInt.erase(0, 1);
	while (strFrac.length() > 1 && strFrac[strFrac.length() - 1] == '0')
		strFrac.erase(strFrac.length() - 1, 1);

	//Cai dat tren co the cai tien them vao so 0
	//Chuyen doi phan nguyen sang he 10
	QInt tempInt = BinToDec(strInt);
	string Int = tempInt.QIntToStrDec();
	//Chuyen doi phan thap phan sang he 10
	string Frac;
	int pos = strFrac.find_last_of('1');
	//Kiem tra phan thap phan khac 0
	if (pos != string::npos) {
		Frac = "5";
		for (int i = pos - 1; i >= 0; i--)
			Frac = mulByHalf(Frac, strFrac[i] == '1');
		Frac = '.' + Frac;
	}
	result = result + Int + Frac;
	return result;
}

//Cong 2 string sau thap phan
string addStr(string a, string b, bool& temp) {
	string result;
	//Do dai 2 chuoi
	int n = a.length();
	temp = 0;
	for (int i = n - 1; i >= 0; i--) {
		int sum = a[i] + b[i] - '0' * 2 + temp;
		char c;
		switch (sum)
		{
		case 0:
			c = '0';
			break;
		case 1:
			c = '1';
			temp = 0;
			break;
		case 2:
			c = '0';
			temp = 1;
			break;
		case 3:
			c = '1';
			temp = 1;
			break;
		}
		result = c + result;
	}
	return result;
}

//Tru 2 string sau thap phan voi a >= b
string subStr(string a, string b) {
	string result;
	int temp = 0;
	int n = a.length();
	for (int i = n - 1; i >= 0; i--) {
		int sub = a[i] - b[i] + temp;
		char c;
		switch (sub)
		{
		case -2:
			c = '0';
			temp = -1;
			break;
		case -1:
			c = '1';
			temp = -1;
			break;
		case 0:
			c = '0';
			temp = 0;
			break;
		case 1:
			c = '1';
			temp = 0;
			break;
		}
		result = c + result;
	}
	return result;
}

int compareStr(string a, string b) {
	int i = 0;
	while (i < a.length()) {
		if (a[i] == b[i])
			i++;
		else
			break;
	}
	if (i == a.length())
		return 0;
	if (a[i] > b[i])
		return 1;
	else
		return -1;
}

//Khoi tao tu chuoi so thuc
Qfloat::Qfloat(string s) {
	(*this) = strDecToQfloat(s);
}

//Nhap so thuc
void Qfloat::ScanQfloat(Qfloat& x, string s, int base) {
	if (base == 2)
		x = BinToDec(s);
	else
		if (base == 10) {
			Qfloat temp = s;
			x = s;
		}
}

//Xuat so thuc
string Qfloat::PrintQfloat(Qfloat x, int base) {
	if (base == 2)
		return DecToBin(x);
	else 
		if (base==10)
			return toStrDec(x);
}

//Chuyen doi Qfloat nhi phan sang thap phan
Qfloat Qfloat::BinToDec(string s) {
	Qfloat res;
	for (int i = 0; i < s.length(); i++)
		res.setBit(MAX_N * BIT - 1 - i, s[i] == '1');
	return res;
}

//Chuyen doi Qfloat thap phan sang nhi phan
string Qfloat::DecToBin(Qfloat x) {
	string res;
	for (int i = MAX_N * BIT - 1; i >= 0; i--)
		if (x.getBit(i))
			res += '1';
		else
			res += '0';
	return res;
}

//Toan tu gan: Qfloat = string
Qfloat& Qfloat::operator=(string s) {
	Qfloat res = s;
	(*this) = res;
	return (*this);
}

Qfloat& Qfloat::operator=(const Qfloat& other) {
	for (int i = 0; i < MAX_N; i++)
		this->data[i] = other.data[i];
	return *this;
}

Qfloat Qfloat::operator+(const Qfloat& other) {
	Qfloat zero;
	//Xet 1 so bang 0
	if (this->isZero())
		return other;
	if (other.isZero())
		return *this;
	//Lay gia tri mu
	int e1, e2, e;
	e1 = this->getExp();
	e2 = other.getExp();
	string strSigni1 = this->getSigni();
	string strSigni2 = other.getSigni();
	//Xac dinh dang chuan hoac khong chuan
	if (e1 == MIN_EXP)
		strSigni1 = '0' + strSigni1;
	else
		strSigni1 = '1' + strSigni1;
	strSigni1.erase(BIT_SIGN, 1);
	e1 += 1;
	if (e2 == MIN_EXP)
		strSigni2 = '0' + strSigni2;
	else
		strSigni2 = '1' + strSigni2;
	strSigni2.erase(BIT_SIGN, 1);
	e2 += 1;
	//Can bang e1, e2
	while (e1 < e2) {
		strSigni1 = '0' + strSigni1;
		strSigni1.erase(BIT_SIGN, 1);
		e1++;
		if (checkStr(strSigni1, '0'))
			return other;
	}
	while (e1 > e2) {
		strSigni2 = '0' + strSigni2;
		strSigni2.erase(BIT_SIGN, 1);
		e2++;
		if (checkStr(strSigni2, '0'))
			return *this;
	}
	e = e1;
	//Xac dinh dau
	bool sign1, sign2, sign;
	sign1 = this->getBit(LEN - 1);
	sign2 = other.getBit(LEN - 1);
	sign = 0;
	string strSigni;
	//Cong (cung dau) hoac tru (neu khac dau)
	if (sign1 == sign2) {
		bool temp = 0;
		sign = sign1;
		strSigni = addStr(strSigni1, strSigni2, temp);
		if (temp) {
			strSigni = '1' + strSigni;
			e++;
		}
	}
	else {
		int com = compareStr(strSigni1, strSigni2);
		switch (com)
		{
		case 0:
			return zero;
			break;
		case 1:
			strSigni = subStr(strSigni1, strSigni2);
			sign = sign1;
			break;
		case -1:
			strSigni = subStr(strSigni2, strSigni1);
			sign = sign2;
			break;
		}
	}
	if (checkStr(strSigni, '0'))
		return zero;
	//Dang chuan
	while (strSigni[0] != '1') {
		e--;
		strSigni.erase(0, 1);
		strSigni = strSigni + '0';
	}
	e--;
	strSigni.erase(0, 1);
	strSigni = strSigni + '0';
	//Xet cac truong hop
	if (e <= MIN_EXP)
		return zero;
	if (e >= MAX_EXP)
		return inf(sign);
	//Tra ve ket qua
	Qfloat result;
	result.setBit(LEN - 1, sign);
	string strExp = toStrBias(e);
	for (int i = 0; i < BIT_EXP; i++)
		result.setBit(LEN - 2 - i, strExp[i] == '1');
	for (int i = 0; i < BIT_SIGN; i++)
		result.setBit(BIT_SIGN - 1 - i, strSigni[i] == '1');
	return result;
}

Qfloat Qfloat::operator-(const Qfloat& other) {
	Qfloat temp = other;
	if (temp.getBit(LEN - 1))
		temp.setBit(LEN - 1, 0);
	else
		temp.setBit(LEN - 1, 1);
	return (*this) + temp;
}

// Tinh tich phan tri
string productQfloat(string a, string b, int& exp)
{
	// Lam day 128 bit cho phan tri
	/*string sub(128 - BIT_SIGN - 1, '0');
	a = sub + a, b = sub + b;*/
	QInt Q = BinToDec(a), M = BinToDec(b);
	//Nhan theo thuat toan Booth: 
	QInt A;
	bool P = 0; // Q_-1: Khoi tao gia tri ban dau la bit 0
	for (int i = 0; i < QINT_SIZE * QINT_LENGTH; i++)
	{
		// Lay bit trai nhat cua Q
		bool LSB_Q = QInt::getBit(Q.data[QINT_LENGTH - 1], QINT_SIZE - 1);

		//TH1: Q_0 = 0, Q_-1 = 1 : A = A + M
		if (P == true && LSB_Q == false)
			A = plusQInt(A, M);
		//TH2: Q_0 = 1, Q_-1 = 0 : A = A - M
		else if (P == false && LSB_Q == true)
			A = substractQInt(A, M);

		//Dich bit
		P = LSB_Q;
		Q = Q >> 1;

		// Dich bit trai nhat cua A sang Q
		if (QInt::getBit(A.data[QINT_LENGTH - 1], QINT_SIZE - 1) == 1)
			QInt::setBit1(Q.data[0], 0);
		else
			QInt::setBit0(Q.data[0], 0);
		A = A >> 1;
	}

	// Tinh lai phan mu
	if ((A.binLen + 128) == ((BIT_SIGN + 1) * 2)) {
		exp++;
	}

	// Tach lay phan tri gom BIT_SIGN + 1 bit
	string result = DecTo128Bin(A) + DecTo128Bin(Q);
	result = result.substr((128 - BIT_SIGN - 1) * 2, BIT_SIGN);

	// Tach bo so 1 giu phan tri
	result.erase(result.begin());
	return result;
}

Qfloat Qfloat::operator*(const Qfloat& other) {
	Qfloat zero;
	//Nhan voi 0
	if (this->isZero() || other.isZero())
		return zero;
	//Lay dau
	bool sign1, sign2, sign;
	sign1 = this->getBit(MAX_N * BIT - 1);
	sign2 = other.getBit(MAX_N * BIT - 1);
	sign = !(sign1 == sign2);
	char strSign = (sign1 == sign2) ? '0' : '1';
	//Lay gia tri mu
	int e1, e2, e;
	e1 = this->getExp();
	e2 = other.getExp();
	e = e1 + e2;
	
	//Lay phan tri
	string s1, s2;
	s1 = '1' + this->getSigni();
	s2 = '1' + other.getSigni();

	string strSigni = productQfloat(s1, s2, e);

	// Kiem tra lai phan mu
	if (e < MIN_EXP)
		return zero;
	if (e > MAX_EXP)
		return inf(sign);
	string strExp = toStrBias(e);


	string result = strSign + strExp + strSigni;
	return BinToDec(result);
}

string divideQFloat(string n, string d, int& exp) {
	QInt dividend = BinToDec(n), remainder;
	QInt divisor = BinToDec(d), zero;
	string result;
	int floatPointAnchor = -1;
	string test;

	for (int i = BIT_SIGN; i >= 0; i--) {
		if (dividend == zero) {
			result.push_back('0');
			continue;
		}
		test = QInt::DecToBin(dividend);
		if (dividend < divisor) {
			result.push_back('0');
			/*if (floatPointAnchor == -1) {
				floatPointAnchor = i + 1;
			}*/
			remainder = dividend;
		}
		else {
			result.push_back('1');
			remainder = dividend - divisor;
		}

		dividend = remainder << 1;
	}

	//// chuan hoa ket qua
	//if (dividend == zero) {
	//	for (int i = 0; i < result.length(); i++) {
	//		if (result[i] == '1') {
	//			floatPointAnchor = result.length() - 1 - i;
	//			exp += BIT_SIGN - floatPointAnchor;
	//			break;
	//		}
	//	}
	//}
	//else  if (floatPointAnchor == BIT_SIGN) {
	//	for (int i = floatPointAnchor; i >= 0; i--) {
	//		if (result[i] == '1') {
	//			floatPointAnchor = i;
	//			break;
	//		}
	//	}

	//	exp -= BIT_SIGN - floatPointAnchor;
	//}

	// xoa cac bit phia truoc
	//result = result.substr(BIT_SIGN + 1 - floatPointAnchor);
	result = result.substr(1);

	return result;
}

Qfloat Qfloat::operator/(const Qfloat& other) {
	Qfloat result;
	// chia cho 0
	if (other.isZero()) {
		for (int i = 0; i < BIT_EXP; i++) {
			result.setBit(i + BIT_SIGN, 1);
		}
		return result;
	}
	// so chia la 0
	if (this->isZero()) {
		return result;
	}

	// lay dau
	bool sign1, sign2, sign;
	sign1 = this->getBit(MAX_N * BIT - 1);
	sign2 = other.getBit(MAX_N * BIT - 1);
	sign = !(sign1 == sign2);
	char strSign = (sign1 == sign2) ? '0' : '1';

	// lay mu
	int exp, exp1, exp2;
	exp1 = this->getExp();
	exp2 = other.getExp();
	exp = exp1 - exp2;
	
	//lay phan tri
	string signi1, signi2;
	signi1 = '1' + this->getSigni();
	signi2 = '1' + other.getSigni();
	
	// thuc hien phep chia va chuan hoa ket qua
	string strSigni = divideQFloat(signi1, signi2, exp);

	if (exp < MIN_EXP)
		return result;
	if (exp > MAX_EXP)
		return inf(sign);
	string strExp = toStrBias(exp);

	string strResult = strSign + strExp + strSigni;
	result = BinToDec(strResult);
	return result;
}

