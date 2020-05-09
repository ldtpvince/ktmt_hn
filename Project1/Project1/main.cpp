#include <iostream>
#include "Qfloat.h"
#include "QInt.h"

using namespace std;

int main(){
	Qfloat x("3.46"), y("1.2"), z;
	z = x * y;
	string testx = x.getSigni();
	string teststr = z.getSigni();
	int testexp = z.getExp();
	cout << Qfloat::PrintQfloat(z, 10);
	return 0;
}