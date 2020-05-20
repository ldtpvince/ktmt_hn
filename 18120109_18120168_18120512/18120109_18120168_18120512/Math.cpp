#include "Math.h"
#include "QInt.h"
#include "Qfloat.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Math::Math()
{

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

	//Bieu thuc nhap vao khac "ERROR"
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
				QInt operand(changeNumeral(a, mode, 10, 1));

				result = ~operand;
				answer = result.QIntToStrDec();
			}
			// Xu ly dich bit
			//Dich trai: <<
			else if (toProcess.find('<') != std::string::npos)
			{
				int pos = toProcess.find('<');
				a = toProcess.substr(0, pos);
				b = toProcess.substr(pos + 2);
				QInt operand(changeNumeral(a, mode, 10, 1));
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
				QInt operand(changeNumeral(a, mode, 10, 1));
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

				QInt operand1(changeNumeral(a, mode, 10, 1)), operand2(changeNumeral(b, mode, 10, 1));

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

	answer = changeNumeral(answer, 10, mode, 1);
	return answer;
}

//Ham su dung de chuyen he tu mode1 sang mode2
std::string Math::changeNumeral(std::string toProcess, int mode1, int mode2, bool type)
{
	std::string answer = toProcess;
	if (type)
	{
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
			else if (mode2 == 16)
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
	}
	else
	{
		if (mode1 != 16 && mode2 != 16)
		{
			Qfloat temp;
			Qfloat::ScanQfloat(temp, toProcess, mode1);
			answer = Qfloat::PrintQfloat(temp, mode2);
		}
	}
	return answer;
}