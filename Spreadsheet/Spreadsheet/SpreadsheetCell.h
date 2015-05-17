#include <string>
using std::string;

class SpreadsheetCell
{
public:
	SpreadsheetCell(){} //老式的默认构造函数
	//C++11显示默认构造函数，它避免了在公有的接口文件中实现任何方法
	//SpreadsheetCell() = default; 
	//如果想定义一个类，而且这个类没有任何构造函数
	//并且不想让编译器自动生成默认构造函数，那么可以
	//使用显示删除构造函数(explicitly deleted constructors)
	//SpreadsheetCell() = delete;
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(string initialValue);
	void setValue(double inValue);
	double getValue() const;
	void setString(string inString);
	string getString() const;
protected:
	string doubleToString(double inValue) const;
	double stringToDouble(string inString) const;
	double mValue;
	string mString;
};