#include<string>
using std::string

class SpreadsheetCell
{
	public:
		SpreadsheetCell(double inValue);
		//const方法 静态方法
		double getValue() const;
		string getString() const;
		
		void setValue(double inValue);
		double getValue() const;
		void setString(string inString);
		srting getString() const;
		//原始版本的加法
		const SpreadsheetCell add(const SpreadsheetCell& cell) const;
		//重载+运算符 这个类作用域内的重载方法对于x = 4 + cell这样的调用会发生错误
		const SpreadsheetCell operator+(const SpreadsheetCell& cell) const;
		//使用explicit关键字标记构造函数，禁止隐式类型转换
		explicit SpreadsheetCell(const string& initialValue); //禁止将string转换成SpreadsheetCell
		//需要将全局的operator+函数声明为类的友元，因为它需要访问该类的protected数据成员
		friend const SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
		friend const SpreadsheetCell operator-(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
		friend const SpreadsheetCell operator*(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
		//需要注意除0
		friend const SpreadsheetCell operator/(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
		
		//重载简写运算符（+=、-=、*=、/=...)
		//这些运算符与算术运算符有两大不同点：
		//1.这些运算符会改变运算符左边的对象，而不是创建一个新对象
		//2.这些运算符左边总是会需要有一个对象，因此它们应该作为类方法，而非全局函数
		SpreadsheetCell& operator+=(const SpreadsheetCell& rhs);
		SpreadsheetCell& operator-=(const SpreadsheetCell& rhs);
		SpreadsheetCell& operator*=(const SpreadsheetCell& rhs);
		SpreadsheetCell& operator/=(const SpreadsheetCell& rhs);
		
		//重载比较运算符
		friend bool operator==(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
		friend bool operator<(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
		friend bool operator>(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
		friend bool operator!=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
		friend bool operator<=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
		friend bool operator>=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
		
	protected:
		//静态方法，必须是非const的
		static string doubleToString(double val);
		static double stringToDouble(const string& str)
		
		double mValue;
		string mString;
		//mutable数据成员，允许const方法改变这一类型数据成员的值
		mutable int mNumAccesses = 0;
};
