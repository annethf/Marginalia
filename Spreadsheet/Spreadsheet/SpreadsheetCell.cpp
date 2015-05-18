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

//复制构造函数
SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell &src) : mValue(src.mValue), mString(src.mString)
{
}

//委托构造函数， 调用了该类中的其他构造函数，但是不能放在构造函数体内，必须在构造函数初始化器中
//需要避免构造函数的递归调用，即应该避免第一个构造函数委托第二个构造函数；第二个构造函数又委托第一个构造函数
SpreadsheetCell::SpreadsheetCell(const string& initialValue) : SpreadsheetCell(stringToDouble(initialValue))
{
}

//赋值运算符
SpreadsheetCell& SpreadsheetCell::operator=(const SpreadsheetCell& rhs)
{
	//自赋值检测
	if (this == &rhs)
		return *this; //返回值是SpreadsheetCell的引用，所以返回*this

	//如果不是自赋值，则必须对每个成员赋值
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