#include "SpreadsheetCell.h"

class Spreadsheet
{
public:
	Spreadsheet(int inWidth, int inHeight);
	Spreadsheet(const Spreadsheet& src);
	~Spreadsheet();
	Spreadsheet& operator=(const Spreadsheet& rhs);
	void copyFrom(const Spreadsheet& src);
	void setCellAt(int x, int y, const SpreadsheetCell& cell);
	SpreadsheetCell getCellAt(int x, int y);
protected:
	bool inRange(int val, int upper);
	int mWidth, mHeight;
	SpreadsheetCell** mCells;

//在类中动态分配内存时，如果只是想禁止其他人复制对象或者为对象赋值，只需将赋值运算符
//以及复制构造函数标记为private。通过这种方法，当其他任何人按值传递对象、从函数或者
//方法返回对象或者为对象赋值时，编译器都会报错。
//下面的代码就能起到禁止对象赋值并按值传递的作用
//private: //不需要提供private赋值构造函数以及赋值运算符的实现。联接器永远不会查看它们。
		 //因为编译器不允许代码调用它们。如果想让子类访问这两类函数，则应将这两个函数设为protected, 而不是private
	//Spreadsheet(const Spreadsheet& src);
	//Spreadsheet& operator=(const Spreadsheet& rhs);
};

