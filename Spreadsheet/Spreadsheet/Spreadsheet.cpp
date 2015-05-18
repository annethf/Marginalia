// Spreadsheet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SpreadsheetCell.h"
#include "PointSequence.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//用初始化列表构造函数初始化对象，其中等号是可选的
	PointSequence p1 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
	//或PointSequence p1{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
	p1.dumpPoints();
	try
	{
		PointSequence p2 = { 1.0, 2.0, 3.0 };
	}
	catch (const invalid_argument& e)
	{
		cout << e.what() << endl;
	}

	return 0;
}

