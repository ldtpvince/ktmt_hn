#include "Math.h"
#include "QInt.h"
#include "Qfloat.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Math::Math()
{
	//Khoi tao nhung ket hop toan tu khong hop le de kiem tra
	this->oper[0] = "/";
	this->oper[1] = "x";
	this->oper[2] = "-";
	this->oper[3] = "+";
	this->oper[4] = ".";

	int operSize = sizeof(oper) / sizeof(std::string); //Kich co cua cac toan tu

	for (int i = 0; i < operSize; i++)
	{
		for (int j = 0; j < operSize; j++)
		{
			this->invalidOper.push_back(oper[i] + oper[j]);
		}
	}


}

Qfloat calcQfloat_clone(Qfloat a, Qfloat b, char sign) {
	switch (sign) {
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	}
}

//Toan tu 1 ki tu
QInt calcQInt_clone(QInt a, QInt b, char sign) {
	switch (sign) {
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	case '&':
		return a & b;
	case '|':
		return a | b;
	case '^':
		return a ^ b;
	}
}

//Xu ly bieu thuc chuoi va tra ve ket qua cho chuoi do
std::string Math::doMath(std::string toProcess, int mode)
{
	std::string answer = toProcess;

	//Kiem tra tinh hop le cua chuoi bieu thuc
	//answer = this->validate(answer);

	//Tinh toan khi chuoi bieu thuc hop le
	if (answer != "ERROR")
	{
		//Kiem tra bieu thuc co chua so phan phan
		int dot = toProcess.find('.');
		if (dot != std::string::npos) //So thap phan
		{
			char opera[] = { '+', '-', '*', '/' };
			std::string a, b;
			char calc = ' ';
			int i = 1;
			for (; i < toProcess.length(); i++)
			{
				//Checking Every Element in the String to see if its an Operator 
				for (int j = 0; j < sizeof(opera) / sizeof(char); j++)
				{
					if (toProcess[i] == opera[j])
					{
						//Kiem tra neu so hang thu 2 la so am
						if (toProcess[i - 1] == calc)
							break;
						//Tim thay so hang
						a = toProcess.substr(0, i);
						b = toProcess.substr(i + 1);
						calc = opera[j];

						break;
					}
				}
			}

			Qfloat operand1, operand2, result;
			Qfloat::ScanQfloat(operand1, a, mode);
			Qfloat::ScanQfloat(operand2, b, mode);
			if (calc != ' ')
			{
				result = calcQfloat_clone(operand1, operand2, calc);
				answer = Qfloat::PrintQfloat(result, mode);
			}
		}
		else //QInt
		{
			QInt result;
			std::string a, b;
			if (toProcess[0] == '~')
			{
				a = toProcess.substr(1);
				QInt operand(changeNumeral(toProcess, mode, 10));

				result = operand;
			}
			// Xu ly dich bit
			//Dich trai: <<
			if (toProcess.find('<') != std::string::npos)
			{
				int pos = toProcess.find('<');
				a = toProcess.substr(0, pos);
				b = toProcess.substr(pos + 2);
				QInt operand(changeNumeral(a, mode, 10));
				int ind = std::stoi(b);
				
				result = operand << ind;
				answer = result.QIntToStrDec();
			}
			//Dich phai: >>
			else if (toProcess.find('>') != std::string::npos)
			{
				int pos = toProcess.find('>');
				a = toProcess.substr(0, pos);
				b = toProcess.substr(pos + 2);
				QInt operand(changeNumeral(a, mode, 10));
				int ind = std::stoi(b);

				result = operand >> ind;
				answer = result.QIntToStrDec();
			}
			else
			{
				char opera[] = { '+', '-', '*', '/', '&', '|', '^' };
				char calc = ' ';
				int i = 1;
				for (; i < toProcess.length(); i++)
				{
					//Checking Every Element in the String to see if its an Operator 
					for (int j = 0; j < sizeof(opera) / sizeof(char); j++)
					{
						if (toProcess[i] == opera[j])
						{
							//Kiem tra neu so hang thu 2 la so am
							if (toProcess[i - 1] == calc)
								break;
							
							a = toProcess.substr(0, i);
							b = toProcess.substr(i + 1);
							calc = opera[j];

							break;
						}
					}
				}

				QInt operand1(changeNumeral(a, mode, 10)), operand2(changeNumeral(b, mode, 10));

				if (calc != ' ')
				{
					result = calcQInt_clone(operand1, operand2, calc);

					//Xac dinh phep chia 0
					if (calc = '/'&& operand2 == QInt::zero())
						answer = "ERROR";
					if (answer != "ERROR")
						answer = result.QIntToStrDec();
				}
			}
		}
	}

	return answer;
}


//Kiem tra bieu thuc chuoi hop le
std::string Math::validate(std::string toProcess)
{
	//Luu ket qua
	std::string answer = toProcess;

	/*
		Kiem tra tinh hop le cua bieu thuc
		1) Khong co 2 toan tu lien ke nhau
		2) Khong bat dau bang toan tu
		3) Khong ket thuc boi 1 toan tu	
	*/

	//Chia chuoi bieu thuc ra thanh 2 ky tu lien tiep cua chuoi
	//Vaf luu moi cap trong moi cap vector
	//So sanh moi cap voi cac ket hop toan tu khong hop le

	std::vector<std::string> pairs;
	bool isOver = false;
	int pos = 0; //Vi tri bat dau
	while (!isOver)
	{
		if (pos + 1 <= toProcess.length())
		{
			pairs.push_back(toProcess.substr(pos,2));
			pos += 1; //Chay ket cap tiep theo
		}
		else
		{
			isOver = true; //Ket thuc vong lap
		}
	}

	//Kiem tra 2 toan khong lien ke nhau
	//So sanh tung cap voi cac ket hop toan tu khong hop le
	for (int i = 0; i < pairs.size(); i++)
	{
		for (int j = 0; j < this->invalidOper.size(); j++)
		{
			if (pairs[i] == this->invalidOper[j])
			{
				answer = "ERROR";
			}
		}
	}

	if (toProcess.length() >= 1)
	{

		//Kiem tra phan tu dau hoac cuoi khong la toan tu
		for (int i = 0; i < sizeof(this->oper) / sizeof(std::string); i++)
		{
			if (toProcess.substr(0, 1) == this->oper[i] ||
				toProcess.substr(toProcess.length() - 1, 1) == this->oper[i])
			{
				answer = "ERROR";
			}
		}
	}
	return answer;
}

//Ham su dung de chuyen he tu mode1 sang mode2
std::string Math::changeNumeral(std::string toProcess, int mode1, int mode2)
{
	std::string answer = toProcess;
	if (mode1 == 10)
	{
		if (mode2 == 2)
			answer = strDecToBin(toProcess);
		else if (mode2 == 16)
		{
			std::string temp = strDecToBin(toProcess);
			answer = BinToHex(temp);
		}
	}
	else if (mode1 == 2)
	{
		if (mode2 == 10)
		{
			QInt temp = BinToDec(toProcess);
			answer = temp.QIntToStrDec();
		}
		else if (mode2 == 16);
			answer = BinToHex(toProcess);
	}
	else //He thap luc
	{
		if (mode2 == 10)
		{
			std::string temp = strHexToBin(toProcess);
			//Chuyen tu he co so 2 sang co so 10
			QInt res = BinToDec(temp);
			answer = res.QIntToStrDec();
		}
		else if (mode2 == 2)
			answer = strHexToBin(toProcess);
	}
	return answer;
}