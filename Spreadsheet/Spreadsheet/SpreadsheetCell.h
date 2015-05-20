#ifndef __SPREADSHEETCELL__
#define __SPREADSHEETCELL__

#include <iostream>
#include <string>
#include <initializer_list>
#include <vector>
using std::string;
using std::endl;
using std::cout;
using std::initializer_list;
using std::invalid_argument;
using std::vector;

class SpreadsheetCell
{
public:
	SpreadsheetCell(){} //老式的默认构造函数
	//c++11显示默认构造函数，它避免了在公有的接口文件中实现任何方法
	//SpreadsheetCell() = default; 
	//如果想定义一个类，而且这个类没有任何构造函数
	//并且不想让编译器自动生成默认构造函数，那么可以
	//使用显示删除构造函数(explicitly deleted constructors)
	//SpreadsheetCell() = delete;
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(string initialValue);
	//复制构造函数 copy constructor
	SpreadsheetCell(const SpreadsheetCell &src);
	//委托构造函数，采用源对象的const引用
	SpreadsheetCell(const string& initialValue);
	//赋值运算符(重载)，采用源对象的const引用；其返回值是被调用对象的引用
	SpreadsheetCell& operator=(const SpreadsheetCell& rhs);
	//可以显示地默认或者删除编译器生成的赋值运算符
	/*SpreadsheetCell& operator=(const SpreadsheetCell& rhs) = default;
	SpreadsheetCell& operator=(const SpreadsheetCell& rhs) = delete;*/
	void setValue(double inValue);
	double getValue() const;
	void setString(string inString);
	string getString() const;

	//静态方法的声明，一个方法声明为静态之后，其后就不能再加const；因为不允许将静态方法声明为const
	//静态方法的语义是这一方法将被应用于全部类对象，而不是单个对象
	static string double2String(double val);

	//static double stringToDouble(const string& str);

protected:
	string doubleToString(double inValue) const;
	double stringToDouble(string inString) const;
	double mValue;
	string mString;

};

#endif
