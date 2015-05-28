#include "SpreadsheetCell.h"
#include <iostream>
#include <sstream>
using namespace std;

SpreadsheetCell::SpreadsheetCell(double inValue)
{	
	setValue(inValue);
}

string SpreadsheetCell::doubleToString(double inValue)
{
	ostringstream ostr;
	ostr << inValue;
	return ostr.str();
}

double SpreadsheetCell::stringToDouble(const string& str)
{
	double temp;
	istringstream istr(str);
	istr >> temp;
	if(istr.fail() || !istr.eof())
		return 0;
	return temp;
}

void SpreadsheetCell::setValue(double inValue)
{
	mValue = inValue;
	mString = doubleToString(mValue);
}

void SpreadsheetCell::setString(string inString)
{
	mString = inString;
	mValue = stringToDouble(mString);
}

//const是方法原型中的一部分，方法的定义必须要加const
double SpreadsheetCell::getValue() const
{
	mNumAccesses++;
	return mValue;
}

string SpreadsheetCell::getString() const
{
	//const方法原则上是不允许修改任何数据成员的
	//但是mutable类型的数据成员除外
	mNumAccesses++;
	return mString;
}

//原始的加法 比较笨拙(是指在调用的时候写起来比较笨)
const SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell& cell) const
{
	SpreadsheetCell newCell; //新建了一个对象
	newCell.setValue(mValue + cell.mValue);
	return newCell; //返回newCell的副本，会调用复制构造函数
					//这里返回的不能是newCell的引用，因为函数返回时newCell将被销毁
}

//重载+运算符 这个在调用的时候就可以写成人们习惯了的 a + b的形式
//除此之外，使用这个函数还可以实现SpreadsheetCell类型的对象与string、int、double
//类型相加
const SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell& cell) const
{
	SpreadsheetCell newCell;
	newCell.setValue(mValue + cell.mValue);
	return newCell;
}

//定义全局的operator+函数，可以满足加法固有的交换率
const SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
	SpreadsheetCell newCell;
	newCell.setValue(lhs.mValue + rhs.mValue);
	return newCell;
}

//重载-运算符
const SpreadsheetCell operator-(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
	return SpreadsheetCell(lhs.mValue - rhs.mValue); //有待测试，书上指明可以；因为这个算是显示调用构造函数吧
}

//重载*运算符
const SpreadsheetCell operator*(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
	return SpreadsheetCell(lhs.mValue * rhs.mValue);
}

//重载/运算符，需要注意除0
const SpreadsheetCell operator/(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
	if(rhs.mValue == 0)
		throw invalid_argument("Divide by zero.");
	return SpreadsheetCell(lhs.mValue / rhs.mValue);
}

//重载简写运算符
SpreadsheetCell& SpreadsheetCell::operator+=(const SpreadsheetCell& rhs)
{
	setValue(mValue + rhs.mValue);
	return *this;
}

SpreadsheetCell& SpreadsheetCell::operator-=(const SpreadsheetCell& rhs)
{
	setValue(mValue - rhs.mValue);
	return *this;
}

SpreadsheetCell& SpreadsheetCell::operaor*=(const SpreadsheetCell& rhs)
{
	setValue(mValue * rhs.mValue);
	return *this;
}

SpreadsheetCell& SpreadsheetCell::operator/=(const SpreadsheetCell& rhs)
{
	if(rhs.mValue == 0)
		throw invalid_argument("Divide by zero.");
	setValue(mValue / rhs.mValue);
	return *this;
}

//重载比较运算符
bool operator==(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
	return (lhs.mValue == rhs.mValue);
}

bool operator<(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
	return (lhs.mValue < rhs.mValue);
}

bool operator>(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
	return (lhs.mValue > rhs.mValue);
}

bool operator!=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
	return (lhs.mValue != rhs.mValue);
	//更好的方法
	//return !(lhs == rhs);
}

bool operator<=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
	return (lhs.mValue <= rhs.mValue;
	//更好的方法
	//return !(lhs > rhs);
}

bool operator>=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
	return (lhs.mValue >= rhs.mValue);
	//更好的方法
	//return !(lhs < rhs);
}















