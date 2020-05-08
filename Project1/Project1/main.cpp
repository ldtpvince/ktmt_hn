#include <iostream>
#include "Qfloat.h"
#include "QInt.h"

using namespace std;

int main(){
	Qfloat x("3.46"), y("1.2"), z, test("1.44166666666666666666");
	string teststr = test.getSigni();
	z = x / y;
	string testres = z.getSigni();
	Qfloat::PrintQfloat(x, 10);
	return 0;
}