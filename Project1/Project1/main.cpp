#include <iostream>
#include <sstream>
#include "Qfloat.h"
#include "QInt.h"

using namespace std;

int main(){
	stringstream str;
	str << "-10000000000000000000000000000000";
	QInt x;
	ScanQInt(str, x, 10);
	PrintQInt(cout, x, 10);
	return 0;
}	