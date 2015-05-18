// Spreadsheet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SpreadsheetCell.h"
#include "PointSequence.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//�ó�ʼ���б��캯����ʼ���������еȺ��ǿ�ѡ��
	PointSequence p1 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
	//��PointSequence p1{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
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

