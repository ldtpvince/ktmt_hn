#include <iostream>
#include "Qfloat.h"
#include "QInt.h"

using namespace std;

int main(){
	QInt x = 12;
	/*ScanQInt(cin, x, 10);
	ScanQInt(cin, y, 10);
	q = x.divide(y, r);*/
	QInt y = 3;
	PrintQInt(cout, x / y, 10);
	/*int i = 10;
	cout << ((i << 28) & (1 << 31));*/
	return 0;
}