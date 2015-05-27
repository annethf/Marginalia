#include "Spreadsheet.h"
Spreadsheet::Spreadsheet(int inWidth, int inHeight):
	mWidth(inWidth), mHeight(inHeight)
{
	mId = sCounter++;
	mCells = new SpreadsheetCell* [mWidth];
	for(int i = 0; i < mWidth; i++)
	{
		mCells[i] = new SpreadsheetCell[mHeight];
	}
}

//添加了静态常量数据成员的构造函数的实现
Spreadsheet::Spreadsheet(int inWidth, int inHeight):
	mWidth(inWidth > kMaxWidth ? kMaxWidth : inWidth),
	mHeight(inHeight > kMaxHeight ? kMaxHeight : inHeight)
{
	mId = sCounter++;
	mCells = new SpreadsheetCell* [mWidth];
	for(int i = 0; i < mWidth; i++)
		mCells[i] = new SpreadsheetCell[mHeight];
}

//添加了引用数据成员的构造函数
Spreadsheet::Spreadsheet(int inWidth, int inHeight, SpreadsheetApplication& theApp):
	mWidth(inWidth > kMaxWidth ? kMaxWidth : inWidth),
	mHeight(inHeigt > kMaxHeigth ? kMaxHeight : inHeigth),
	mTheApp(theAPP)
{
	mId = sCounter++;
	mCells = new SpreadsheetCell* [mWidth];
	for(int i = 0; i < mWidth; i++)
		mCells[i] = new SpreadsheetCell[mHeigth];
}

void Spreadsheet::setCellAt(int x, int y, const SpreadsheetCell& cell)
{
	if(!inRange(x, mWidth) || !inRange(y, mHeight))
		throw std::out_of_range("");
	mCells[x][y] = cell;
}

SpreadsheetCell Spreadsheet::getCellAt(int x, int y)
{
	if(!inRange(x, mWidth) || !inRange(y, mHeight))
		throw std::out_of_range("");
	return mCells[x][y];
}

Spreadsheet::~Spreadsheet()
{
	for(int i = 0; i < mWidth; i++)
		delete [] mCells[i];
	delete [] mCells;
	mCells = nullptr;
}

Spreadsheet::Spreadsheet(const Spreadsheet& src)
{
    mId = sCounter++;
	mWidth = src.mWidth;
	mHeight = src.mHeight;
	mCells = new SpreadsheetCell* [mWidth];
	for(int i = 0; i < mWidth; i++)
		mCells[i] = new SpreadsheetCell[mHeight];
		
	//复制深层数据
	for(int i = 0; i < mWidth; i++)
		for(int j = 0; j < mHeight; j++)
			mCells[i][j] = src.mCells[i][j];
}

//添加了引用数据成员的复制构造函数的实现
Spreadsheet::Spreadsheet(const Spreadsheet& src):
	mTheApp(src.theApp)
{
	mId = sCounter++;
	mWidth = src.mWidth;
	mHeight = src.mHeight;
	mCells = new SpreadsheetCell* [mWidth];
	for(int i = 0; i < mWidth; i++)
		mCells[i] = new SpreadsheetCell[mHeight];
	
	for(int i = 0; i < mWidth; i++)
		for(int j = 0; j < mHeigth; j++)
			mCells[i][j] = src.mCells[i][j];
}

Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs)
{
	//自赋值检测
	if(this == *rhs)
		return *this;
	//释放原来的内存
	for(int i = 0; i < mWidth; i++)
		delete [] mCells[i];
	delete [] mCells;
	
	//分配新内存
	mWidth = rhs.mWidth;
	mHeight = rhs.mHeight;
	
	//在初始化一个引用之后，不能改变它引用的对象。
	//因此不需要在这里对引用复制
	
	mCells = new SpreadsheetCell* [mWidth];
	for(int i = 0; i < mWidth; i++)
		mCells[i] = new SpreadsheetCell[mHeight];
	return *this;
}

int Spreadsheet::getId() const
{
	return mId;
}








































