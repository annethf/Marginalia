// Spreadsheet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Spreadsheet.h"

//可以在类的任意地方访问共有的静态数据成员
int height = Spreadsheet::kMaxHeight;

Spreadsheet::Spreadsheet(int inWidth, int inHeight, SpreadsheetApplication& theApp) :
	mWidth(inWidth < kMaxWidth ? inWidth : kMaxWidth),
	mHeight(inHeight < kMaxHeight ? inHeight : kMaxHeight), mTheApp(theApp)
{
	//动态分配二维数组
	mCells = new SpreadsheetCell*[mWidth];
	for (int i = 0; i < mWidth; i++)
		mCells[i] = new SpreadsheetCell[mHeight];
}

//复制构造函数以及赋值运算符的通用辅助历程，
//有了这个函数，复制构造函数以及赋值运算符中就不需要重复写这些相同的代码了，只要调用这一函数就行
//这里为了明确复制构造函数以及赋值运算符的步骤，不进行调用；尽管如此，实际代码中应该采用调用该函数的方式
void Spreadsheet::copyFrom(const Spreadsheet& src)
{
	mWidth = src.mWidth;
	mHeight = src.mHeight;
	mCells = new SpreadsheetCell*[mWidth];
	for (int i = 0; i < mWidth; i++)
		mCells[i] = new SpreadsheetCell[mHeight];
	for (int i = 0; i < mWidth; i++)
		for (int j = 0; j < mHeight; j++)
			mCells[i][j] = src.mCells[i][j];
}

//复制构造函数，在这里不需要删除已有的二维指针mCells，因为这是一个复制构造函数，因此在this对象中还没有mCells
Spreadsheet::Spreadsheet(const Spreadsheet& src) : mTheApp(src.mTheApp)
{
	mWidth = src.mWidth;
	mHeight = src.mHeight;
	mCells = new SpreadsheetCell*[mWidth];
	for (int i = 0; i < mWidth; i++)
		mCells[i] = new SpreadsheetCell[mHeight];
	//对指针进行深层复制
	for (int i = 0; i < mWidth; i++)
		for (int j = 0; j < mHeight; j++)
			mCells[i][j] = src.mCells[i][j];
}

Spreadsheet::~Spreadsheet()
{
	//释放动态分配的二维数组
	for (int i = 0; i < mWidth; i++)
		delete[] mCells[i];
	delete[] mCells;
	mCells = nullptr;
}

//赋值运算符，当对象被赋值的时候已经被初始化过了，因此，必须在分配新的内存之前释放已分配的动态内存
Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs)
{
	//自赋值检测
	if (this == &rhs)
		return *this;
	//释放旧指针
	for (int i = 0; i < mWidth; i++)
		delete[] mCells[i];
	delete[] mCells;
	mCells = nullptr; //指针释放之后，一定要有这一步

	//复制新内存
	mWidth = rhs.mWidth;
	mHeight = rhs.mHeight;
	mCells = new SpreadsheetCell* [mWidth];
	for(int i = 0; i < mWidth; i++)
		mCells[i] = new SpreadsheetCell[mHeight];
	for (int i = 0; i < mWidth; i++)
		for (int j = 0; j < mHeight; j++)
			mCells[i][j] = rhs.mCells[i][j];
	return *this;
}

void Spreadsheet::setCellAt(int x, int y, const SpreadsheetCell& cell)
{
	if (!inRange(x, mWidth) || !inRange(y, mHeight))
	{
		throw std::out_of_range("");
	}
	mCells[x][y] = cell;
}

SpreadsheetCell Spreadsheet::getCellAt(int x, int y)
{
	if (!inRange(x, mWidth) || !inRange(y, mHeight))
	{
		throw std::out_of_range("");
	}
	return mCells[x][y];
}

bool Spreadsheet::inRange(int val, int upper)
{
	if (val != upper)
		return true;
	return false;
}