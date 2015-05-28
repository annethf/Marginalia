#include "SpreadsheetCell.h"
#include <iostream>
#include <sstream>
using namespace std;

StringSpreadsheetCell::StringSpreadsheetCell() : mValue("#NOVALUE") {}

StringSpreadsheetCell::StringSpreadsheetCell(const DoubleSpreadsheetCell& inDoubleCell)
{
	mValue = doubleToString(inDoubleCell.mValue);
	return *this;
}

void StringSpreadsheetCell::set(const string& inString)
{
	mValue = inString;
}

string StringSpreadsheetCell::getString() const
{
	return mValue;
}

DoubleSpreadsheetCell::DoubleSpreadsheetCell() : mValue(std::numeric_limits<double>::quiet_NaN()) {}

void DoubleSpreadsheetCell::set(double inDouble)
{
	mValue = inDouble;
}

void DoubleSpreadsheetCell::set(const string& inString)
{
	mValue = stringToDouble(inString);
}

string DoubleSpreadsheetCell::getString() const
{
	return doubleToString(mValue);
}

string DoubleSpreadsheetCell::doubleToString(double inValue)
{
	ostringstream ostr;
	ostr << inValue;
	return ostr.str();
}

double DoubleSpreadsheetCell::stringToDouble(const string& inValue)
{
	double temp;
	istringstream istr(inString);
	istr >> temp;
	if(istr.fail() || !istr.eof())
		return 0;
	return temp;
} 


