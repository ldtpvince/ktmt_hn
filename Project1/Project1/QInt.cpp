#include "QInt.h"
using namespace std;

QInt::QInt() {
	for (int i = 0; i < QINT_LENGTH;i++) {
		data[i] = 0;
	}
	binLen = 0;
}

QInt::QInt(unsigned int dec) {
	for (int i = 0; i < QINT_LENGTH - 1; i++) {
		data[i] = 0;
	}
	data[QINT_LENGTH - 1] = dec;
	binLen = QIntBinSize();
}

QInt::QInt(string dec) {
	string bin = strDecToBin(dec);
	*this = BinToDec(bin);
}

int QInt::QIntBinSize() {
	int countSize = 0;
	for (int i = 127; i >= 0; i--) {
		if (getBitAt(i) == 1) {
			break;
		}
		countSize++;
	}
	binLen = 128 - countSize;
	return binLen;
}

// ------------------------------------------------------Ham kiem tra so am----------------------------------------------------
// Ham kiem tra chuoi thap phan co am hay khong
bool isNegativeDec(string& dec) {
	if (dec[0] == '-') {
		dec.erase(0, 1);
		return true;
	}
	return false;
}

// Ham kiem tra chuoi nhi phan co am hay khong
bool isNegativeBin(string bin) {
	if (bin[0] == '1') {
		return true;
	}
	return false;
}

//Kiem tra QInt la so am hay khong
bool QInt::isNegative() const
{
	// Kiem tra bit dau tien
	return getBit((*this).data[0], 0) == 1;
}

// ------------------------------------------------------Ham xử lý trên bit----------------------------------------------------
int QInt::setBit0(int& data, int offset) {
	data = (data & ~(1 << (31 - offset)));
	return (data & ~(1 << (31 - offset)));
}

int QInt::setBit1(int& data, int offset) {
	data = data | (1 << (31 - offset));
	return data;
}

//Tra ve gia tri cua bit thu offset
int QInt::getBit(int data, int offset) {
	return (data >> (31 - offset) & 1);
}

int QInt::getBitAt(int pos) {
	return getBit(data[3 - pos / 32], 31 - pos % 32);
}

void QInt::setBitAt(int pos, bool type) {
	int countSize = 0;
	if (type == 1) {
		setBit1((*this).data[3 - pos / 32], 31 - pos % 32);
	}
	else {
		setBit0((*this).data[3 - pos / 32], 31 - pos % 32);
	}

	for (int i = 127; i >= 0; i--) {
		if (getBitAt(i) == 1) {
			break;
		}
		countSize++;
	}
	binLen = 128 - countSize;
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

// ------------------------------------------------------Ham chuyen doi----------------------------------------------------
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
QInt BinToDec(string bin) {
	QInt result;
	int countSize = 0;

	for (int i = bin.size() - 1 ; i  >= 0; i--) {
		if (bin[i] == '1') {
			QInt::setBit1(result.data[3 - (bin.size() - i - 1) / 32], 31 - bin.size() + 1 + i);
		}
	}
	
	for (int i = 0; i < bin.size(); i++) {
		if (bin[i] == '1') {
			break;
		}
		countSize++;
	}
	result.binLen = bin.size() - countSize;

	return result;
}

// Ham chuyen tu sothap phan QInt sang chuoi nhi phan
string DecToBin(QInt x) {
	string result = {};

	for (int i = 0; i < x.binLen; i++) {
		char bit = x.getBit(x.data[3 - i / 32], 31 - i % 32) + '0';
		result.insert(result.begin(), bit);
	}

	return result;
}

// Ham chuyen tu chuoi thap luc phan sang chuoi nhi phan
string BinToHex(string hex) {
	return strHexToBin(hex);
}

// Ham chuyen tu so thap phan QInt sang chuoi thap luc phan
string DecToHex(QInt x) {
	string temp = DecToBin(x);
	return strHexToBin(temp);
}

string QInt::QIntToStrDec() {
	QInt d = 10, q = *this, r;
	string result = {};
	char c;
	bool sign = getBitAt(QINT_SIZE * QINT_LENGTH - 1);
	do {
		q = q.divide(d, r);
		c = r.getBitAt(0) + r.getBitAt(1) * 2 + r.getBitAt(2) * 4 + r.getBitAt(3) * 8 + '0';
		result.insert(result.begin(), c);
		r = 0;
	} while (q.binLen > 0);
	if (sign) {
		result.insert(result.begin(), '-');
	}
	return result;
}

string QInt::toSignedNumber(bool& sign) {
	QInt temp = *this;
	sign = getBitAt(QINT_SIZE * QINT_LENGTH - 1);

	if (sign == 0) {
		return DecTo128Bin(*this);
	}
	else {
		bool first1Bit = false;
		for (int i = 0; i < binLen; i++) {
			bool bit = temp.getBitAt(i);
			
			if (!first1Bit) {
				if (bit == 1) {
					first1Bit = true;
				}
				continue;
			}

			temp.setBitAt(i, !bit);
		}
	}

	return DecTo128Bin(temp);
}

// ------------------------------------------------------Ham scan----------------------------------------------------
// Ham nhap mot chuoi so va luu vao QInt voi co so tuong ung
void ScanQInt(istream& in, QInt& x, int base) {
	string temp;
	in >> temp;
	int numlen = temp.size();

	switch (base) {
	case 2: {
		x = BinToDec(temp);
		break;
	}
	case 10: {
		x = BinToDec(strDecToBin(temp));
		break;
	}
	case 16: {
		x = BinToDec(strHexToBin(temp));
		break;
	}
	}
}

// ------------------------------------------------------Ham print----------------------------------------------------
// Gom 3 ham chuyen tu QInt -> string nhi phan -> chuyen qua cac co so khac nhu thap phan hay thap luc phan
void PrintQInt(std::ostream& out, QInt x, int base) {
	string result;

	switch (base) {
	case 2: {
		out << DecToBin(x);
		break;
	}
	case 10: {
		out << x.QIntToStrDec();
		break;
	}
	case 16: {
		out << DecToHex(x);
		break;
	}
	}

	out << result;
}

//Ham chuyen doi tu thap phan sang nhi phan
string DecTo128Bin(QInt x)
{
	string bits(128, ' ');
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 32; j++)
		{
			if (x.getBit(x.data[i], j) == 1)
				bits[i * 32 + j] = '1';
			else bits[i * 32 + j] = '0';
		}
	return bits;
}

//QInt BinToDec(string bits)
//{
//	QInt Result;
//	for (int i = 0; i < 4; i++)
//		for (int j = 0; j < 32; j++)
//			if (bits[i * 32 + j] == 1)
//				Result.data[i] = QInt::setBit1(Result.data[i], j);
//	return Result;
//}

QInt QInt::operator +(const QInt& x) const
{
	QInt result = plusQInt(*this, x);

	bool isANegative = (*this).isNegative();
	bool isxNegative = x.isNegative();
	//Kiem tra tran so: TH tran so: A, x cung dau va tong trai dau
	if ((isANegative + isxNegative != 1) && (isANegative != result.isNegative()))
	{
		throw "OVERFLOW";
	}
	return result;
}

QInt QInt::operator -(const QInt& x) const
{
	QInt result = substractQInt(*this, x);

	bool isANegative = (*this).isNegative();
	bool isxNegative = x.isNegative();
	//Kiem tra tran so: TH tran so: A, x khac dau va hieu trai dau voi so bi tru
	if ((isANegative + isxNegative == 1) && (isANegative != result.isNegative()))
	{
		throw "OVERFLOW";
	}
	return result;
}

QInt QInt::operator* (const QInt& M) const
{
	//Kiem tra nhan voi 0
	if ((*this) == QInt::zero() || M == QInt::zero())
		return QInt();
	// Truong hop tran so dac biet
	if ((*this == QInt::min() && M == QInt::negativeOne()) || (*this == QInt::negativeOne() && M == QInt::min()))
	{
		throw "OVERFLOW";
		return QInt();
	}
	//Nhan theo thuat toan Booth:
	QInt A;
	QInt Q = *this;
	bool P = 0; // Q_-1: Khoi tao gia tri ban dau la bit 0
	for (int i = 0; i < QINT_SIZE * QINT_LENGTH; i++)
	{
		// Lay bit trai nhat cua Q
		bool LSB_Q = getBit(Q.data[QINT_LENGTH - 1], QINT_SIZE - 1);

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
		if (getBit(A.data[QINT_LENGTH - 1], QINT_SIZE - 1) == 1)
			setBit1(Q.data[0], 0);
		else
			setBit0(Q.data[0], 0);
		A = A >> 1;
	}
	//Kiem tra tran so
	if (Q / M != *this)
	{
		throw "OVERFLOW";
		return QInt();
	}
	return Q;
}

QInt QInt::divide(const QInt& div, QInt& r) const{
	bool isNegative = false;
	QInt d = div, n = (*this);
	QInt zero, result;
	if (n.isNegative()) {
		n = zero - n;
		isNegative = !isNegative;
	}

	if (d.isNegative()) {
		d = zero - d;
		isNegative = !isNegative;
	}

	for (int i = n.binLen - 1; i >= 0; i--) {
		r = r << 1;
		bool bit = n.getBitAt(i);
		r.setBitAt(0, bit);

		if (r >= d) {
			r = r - d;
			result.setBitAt(i, 1);
		}
	}
	
	if (isNegative) {
		return zero - result;
	}
	return result;
}

QInt QInt::operator/ (const QInt& x) const
{
	QInt r;
	return (*this).divide(x, r);
}

//Cac toan tu so sanh va gan
bool QInt::operator> (const QInt& x) const
{
	bool isANegative = (*this).isNegative();
	bool isxNegative = x.isNegative();
	//Hai so trai dau
	if (isANegative != isxNegative)
	{
		return (isANegative == false);
	}

	string a = DecTo128Bin(*this), b = DecTo128Bin(x);
	//Hai so cung dau
	int index = 1;
	while (a[index] == b[index])index++;
	return (a[index] == '1' && index < 128);
}

bool QInt::operator< (const QInt& x) const
{
	bool isANegative = (*this).isNegative();
	bool isxNegative = x.isNegative();
	//Hai so trai dau
	if (isANegative != isxNegative)
	{
		return (isANegative == true);
	}

	string a = DecTo128Bin(*this), b = DecTo128Bin(x);
	//Hai so cung dau
	int index = 1;
	while (a[index] == b[index] && index < 128)index++;
	return (a[index] == '0' && index < 128);
}

bool QInt::operator== (const QInt& x) const
{
	for (int i = 0; i < QINT_LENGTH; i++)
		if ((*this).data[i] != x.data[i])
			return false;
	return true;
}

bool QInt::operator!= (const QInt& x) const
{
	// Phu dinh cua toan tu bang
	return !((*this) == x);
}

bool QInt::operator>= (const QInt& x) const
{
	//Phu dinh toan tu be hon
	return !((*this) < x);
}

bool QInt::operator<= (const QInt& x) const
{
	//Phu dinh toan tu lon hon
	return !((*this) > x);
}

QInt& QInt::operator= (const QInt& x)
{
	for (int i = 0; i < QINT_LENGTH; i++) 
		(*this).data[i] = x.data[i];
	(*this).binLen = x.binLen;
	return (*this);
}

//Toan tu logic
QInt QInt::operator& (const QInt& x) const
{
	QInt Ketqua;
	for (int i = 0; i < 4; i++)
		Ketqua.data[i] = ((*this).data[i] & x.data[i]);
	Ketqua.binLen = Ketqua.QIntBinSize();
	return Ketqua;
}

QInt QInt::operator| (const QInt& x) const
{
	QInt Ketqua;
	for (int i = 0; i < QINT_LENGTH; i++)
		Ketqua.data[i] = ((*this).data[i] | x.data[i]);
	Ketqua.binLen = Ketqua.QIntBinSize();
	return Ketqua;
}

QInt QInt::operator^ (const QInt& x) const
{
	QInt Ketqua;
	for (int i = 0; i < 4; i++)
		Ketqua.data[i] = ((*this).data[i] ^ x.data[i]);
	Ketqua.binLen = Ketqua.QIntBinSize();
	return Ketqua;
}

QInt QInt::operator~ () const
{
	QInt Ketqua;
	for (int i = 0; i < 4; i++)
		Ketqua.data[i] = (~(*this).data[i]);
	Ketqua.binLen = Ketqua.QIntBinSize();
	return Ketqua;
}

QInt QInt::operator <<(int index) const
{
	// Chuyen QInt ve day bit
	string a = DecTo128Bin(*this);
	//Ghi lai bit dau
	char bit_dau = a[0];
	a = a.substr(index);
	string b;
	for (int i = 0; i < index; i++) {
		b.push_back('0');
	}
	a = a + b;
	// Gan lai bit dau
	QInt Result = BinToDec(a);
	return Result;
}

QInt QInt::operator>> (int index) const
{
	// Chuyen QInt ve day bit
	string a = DecTo128Bin(*this);
	//Ghi lai bit dau
	char bit_dau = a[0];
	a = a.substr(0, 128 - index);
	string b(index, bit_dau);
	a = b + a;
	QInt Result = BinToDec(a);
	return Result;
}

QInt QInt::rol(int nums) const
{
	// Chuyen QInt ve day bit
	string a = DecTo128Bin(*this);
	//Ghi lai cac bit ben trai
	string left = a.substr(0, nums);
	a = a.substr(nums);
	// Chuyen nums bit trai ve cuoi
	a = a + left;
	QInt Result = BinToDec(a);
	return Result;
}

QInt QInt::ror(int nums) const
{
	// Chuyen QInt ve day bit
	string a = DecTo128Bin(*this);
	//Ghi lai cac bit ben phai
	string right = a.substr(128 - nums);
	a = a.substr(0, 128 - nums);
	// Chuyen nums bit phai len dau
	a = right + a;
	QInt Result = BinToDec(a);
	return Result;
}

//CAC HAM PHU

QInt QInt::zero()
{
	static QInt staticZero;
	static bool zeroInit = false;
	if (!zeroInit)
	{
		for (int i = 0; i < 4; i++)
			staticZero.data[i] = 0;
		zeroInit = true;
	}
	return staticZero;
}

QInt QInt::negativeOne()
{
	static QInt staticNegativeOne;
	static bool negativeOneInit = false;
	if (!negativeOneInit)
	{
		for (int i = 0; i < QINT_LENGTH; i++)
			staticNegativeOne.data[i] = -1;
		negativeOneInit = true;
	}
	return staticNegativeOne;
}

QInt QInt::min()
{
	static QInt staticMin;
	static bool minInit = false;
	if (!minInit)
	{
		for (int i = 0; i < 4; i++)
			staticMin.data[i] = 0;
		//Set bit dau thanh 1
		setBit1(staticMin.data[0], 0);
		minInit = true;
	}
	return staticMin;
}

// Phep cong, tru khong xu ly tran so
QInt plusQInt(const QInt& x, const QInt& y)
{
	string result(128, ' ');
	string a = DecTo128Bin(x), b = DecTo128Bin(y);
	// Bit nho
	char bit_Carry = '0';
	for (int i = QINT_LENGTH * QINT_SIZE - 1; i >= 0; i--)
	{
		// TH: 1 + 1 || 0 + 0
		if (a[i] == b[i])
		{
			if (a[i] == '0')
				result[i] = bit_Carry, bit_Carry = '0';
			else
				result[i] = bit_Carry, bit_Carry = '1';
		}
		//TH: 0 + 1 || 1 + 0
		else
		{
			if (bit_Carry == '0')
				result[i] = '1', bit_Carry = '0';
			else
				result[i] = '0', bit_Carry = '1';
		}
	}
	QInt _result = BinToDec(result);
	return _result;
}

QInt substractQInt(const QInt& x, const QInt& y)
{
	string result(128, ' ');
	string a = DecTo128Bin(x), b = DecTo128Bin(y);
	// Bit nho
	char bit_Carry = '0';
	for (int i = QINT_LENGTH * QINT_SIZE - 1; i >= 0; i--)
	{
		// TH: 1 - 1 || 0 - 0
		if (a[i] == b[i])
		{
			if (bit_Carry == '0')
				result[i] = '0', bit_Carry = '0';
			else
				result[i] = '1', bit_Carry = '1';
		}
		// TH: 1 - 0 || 0 - 1
		else
		{
			if (a[i] == '0')
			{
				if (bit_Carry == '1')
					result[i] = '0', bit_Carry = '1';
				else
					result[i] = '1', bit_Carry = '1';
			}
			else if (a[i] == '1')
			{
				if (bit_Carry == '1')
					result[i] = '0', bit_Carry = '0';
				else
					result[i] = '1', bit_Carry = '0';
			}
		}
	}
	QInt _result = BinToDec(result);
	return _result;
}

// Tinh tich phan tri
string productQfloat(string a, string b)
{
	// Lam day 128 bit cho phan tri
	string sub(128 - BIT_SIGN - 1, '0');
	a = sub + a, b = sub + b;
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
	// Tach lay phan tri gom BIT_SIGN + 1 bit
	string result = DecTo128Bin(A) + DecTo128Bin(Q);
	result = result.substr((128 - BIT_SIGN - 1) * 2, BIT_SIGN + 1);
	return result;
}