// Spreadsheet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Spreadsheet.h"

//�������������ط����ʹ��еľ�̬���ݳ�Ա
int height = Spreadsheet::kMaxHeight;

Spreadsheet::Spreadsheet(int inWidth, int inHeight, SpreadsheetApplication& theApp) :
	mWidth(inWidth < kMaxWidth ? inWidth : kMaxWidth),
	mHeight(inHeight < kMaxHeight ? inHeight : kMaxHeight), mTheApp(theApp)
{
	//��̬�����ά����
	mCells = new SpreadsheetCell*[mWidth];
	for (int i = 0; i < mWidth; i++)
		mCells[i] = new SpreadsheetCell[mHeight];
}

//���ƹ��캯���Լ���ֵ�������ͨ�ø������̣�
//����������������ƹ��캯���Լ���ֵ������оͲ���Ҫ�ظ�д��Щ��ͬ�Ĵ����ˣ�ֻҪ������һ��������
//����Ϊ����ȷ���ƹ��캯���Լ���ֵ������Ĳ��裬�����е��ã�������ˣ�ʵ�ʴ�����Ӧ�ò��õ��øú����ķ�ʽ
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

//���ƹ��캯���������ﲻ��Ҫɾ�����еĶ�άָ��mCells����Ϊ����һ�����ƹ��캯���������this�����л�û��mCells
Spreadsheet::Spreadsheet(const Spreadsheet& src) : mTheApp(src.mTheApp)
{
	mWidth = src.mWidth;
	mHeight = src.mHeight;
	mCells = new SpreadsheetCell*[mWidth];
	for (int i = 0; i < mWidth; i++)
		mCells[i] = new SpreadsheetCell[mHeight];
	//��ָ�������㸴��
	for (int i = 0; i < mWidth; i++)
		for (int j = 0; j < mHeight; j++)
			mCells[i][j] = src.mCells[i][j];
}

Spreadsheet::~Spreadsheet()
{
	//�ͷŶ�̬����Ķ�ά����
	for (int i = 0; i < mWidth; i++)
		delete[] mCells[i];
	delete[] mCells;
	mCells = nullptr;
}

//��ֵ������������󱻸�ֵ��ʱ���Ѿ�����ʼ�����ˣ���ˣ������ڷ����µ��ڴ�֮ǰ�ͷ��ѷ���Ķ�̬�ڴ�
Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs)
{
	//�Ը�ֵ���
	if (this == &rhs)
		return *this;
	//�ͷž�ָ��
	for (int i = 0; i < mWidth; i++)
		delete[] mCells[i];
	delete[] mCells;
	mCells = nullptr; //ָ���ͷ�֮��һ��Ҫ����һ��

	//�������ڴ�
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