#include "SpreadsheetCell.h"

//前置声明 forward declaration
class SpreadsheetApplication;

class Spreadsheet
{
public:
	Spreadsheet(int inWidth, int inHeight, SpreadsheetApplication& theApp);
	Spreadsheet(const Spreadsheet& src);
	~Spreadsheet();
	Spreadsheet& operator=(const Spreadsheet& rhs);
	void copyFrom(const Spreadsheet& src);
	void setCellAt(int x, int y, const SpreadsheetCell& cell);
	SpreadsheetCell getCellAt(int x, int y);

public:
	static const int kMaxHeight = 100; //静态常量数据成员
	static const int kMaxWidth = 100;

protected:
	bool inRange(int val, int upper);
	int mWidth, mHeight;
	SpreadsheetCell** mCells;
	//引用数据成员，在初始化列表中初始化
	SpreadsheetApplication& mTheApp;
	//C++11中的静态数据成员
	//static int sCounter = 0; //这句话在新标准中是支持的，可以在类内部初始化静态数据成员；而旧标准中
							 //静态数据成员需要在类外进行初始化
	int mId = 0; //C++11支持类内初始化

//在类中动态分配内存时，如果只是想禁止其他人复制对象或者为对象赋值，只需将赋值运算符
//以及复制构造函数标记为private。通过这种方法，当其他任何人按值传递对象、从函数或者
//方法返回对象或者为对象赋值时，编译器都会报错。
//下面的代码就能起到禁止对象赋值并按值传递的作用
//private: //不需要提供private赋值构造函数以及赋值运算符的实现。联接器永远不会查看它们。
		 //因为编译器不允许代码调用它们。如果想让子类访问这两类函数，则应将这两个函数设为protected, 而不是private
	//Spreadsheet(const Spreadsheet& src);
	//Spreadsheet& operator=(const Spreadsheet& rhs);
};

