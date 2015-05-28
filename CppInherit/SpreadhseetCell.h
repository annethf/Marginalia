#include <string>
using std::string;

//抽象类
class SpreadsheetCell
{
	public:
		SpreadsheetCell();
		virtual ~SpreadsheetCell();
		virtual void set(const string& inString) = 0;
		virtual string getString() const = 0;
};

class StringSpreadsheetCell : public SpreadsheetCell
{
	public:
		StringSpreadsheetCell();
		//类型转换构造函数 用来进行同级对象之间的转换
		StringSpreadsheetCell(const DoubleSpreadsheetCell& inDoubleCell);
		virtual void set(const string& inString);
		virtual string getString() const;
	protected:
		string mValue;
};

class DoubleSpreadsheetCell : public SpreadsheetCell
{
	public:
		DoubleSpreadsheetCell();
		virtual void set(double inDouble);
		virtual void set(const string& inString);
		virtual string getString() const;
	protected:
		static string doubleToString(double inValue);
		static double stringToDouble(const string& inValue);
		double mValue;
};
