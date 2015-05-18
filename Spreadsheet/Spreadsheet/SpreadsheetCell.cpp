#include "stdafx.h"
#include "SpreadsheetCell.h"
#include <iostream>
#include <sstream>

using namespace std;

SpreadsheetCell::SpreadsheetCell(double initialValue)
{
	setValue(initialValue);
}

SpreadsheetCell::SpreadsheetCell(string initialValue) : mValue(stringToDouble(initialValue)), mString(initialValue)
{
	setString(initialValue);
}

//���ƹ��캯��
SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell &src) : mValue(src.mValue), mString(src.mString)
{
}

//ί�й��캯���� �����˸����е��������캯�������ǲ��ܷ��ڹ��캯�����ڣ������ڹ��캯����ʼ������
//��Ҫ���⹹�캯���ĵݹ���ã���Ӧ�ñ����һ�����캯��ί�еڶ������캯�����ڶ������캯����ί�е�һ�����캯��
SpreadsheetCell::SpreadsheetCell(const string& initialValue) : SpreadsheetCell(stringToDouble(initialValue))
{
}

//��ֵ�����
SpreadsheetCell& SpreadsheetCell::operator=(const SpreadsheetCell& rhs)
{
	//�Ը�ֵ���
	if (this == &rhs)
		return *this; //����ֵ��SpreadsheetCell�����ã����Է���*this

	//��������Ը�ֵ��������ÿ����Ա��ֵ
	mValue = rhs.mValue;
	mString = rhs.mString;
	return *this;
}

void SpreadsheetCell::setValue(double inValue)
{
	mValue = inValue;
	mString = doubleToString(mValue);
}

double SpreadsheetCell::getValue() const
{
	return mValue;
}

void SpreadsheetCell::setString(string inString)
{
	mString = inString;
	mValue = stringToDouble(inString);
}

string SpreadsheetCell::getString() const
{
	return mString;
}

string SpreadsheetCell::doubleToString(double inValue) const
{
	ostringstream ostr;
	ostr << inValue;
	return ostr.str();
}

double SpreadsheetCell::stringToDouble(string inString) const
{
	double temp;
	istringstream istr(inString);
	istr >> temp;
	if (istr.fail() || !istr.eof())
	{
		return 0;
	}
	return temp;
}