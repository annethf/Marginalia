
//#include "SpreadsheetCell.h"
//#include <iostream>
//#include <memory>
//
//using namespace std;
//
//int main(int argc, char *argv)
//{
//	SpreadsheetCell myCell1, anotherCell2;
//	myCell1.setValue(6);
//	anotherCell2.setString("3.2");
//	cout << "cell 1: " << myCell1.getValue() << endl;
//	cout << "cell 2: " << anotherCell2.getValue() << endl;
//	//普通指针
//	//C++用new进行初始化的规律：
//	//对于有构造函数的类，不论有没有括号，都用构造函数进行初始化；
//	//如果没有构造函数，则不加括号的new只分配内存空间，不进行内存的初始化
//	SpreadsheetCell* myCell3 = new SpreadsheetCell();
//	//或SpreadsheetCell* myCellp = new SpreadsheetCell();
//	myCell3->setValue(3.7);
//	cout << "cellp 3: " << myCell3->getValue() << " "
//		<< myCell3->getString() << endl;
//	delete myCell3;
//	myCell3 = nullptr;
//	//智能指针(C++11)
//	shared_ptr<SpreadsheetCell> myCell4(new SpreadsheetCell());
//	myCell4->setValue(3.7);
//	cout << "cell 3: " << myCell4->getValue() << " cell 4: "
//		<< myCell4->getString() << endl;
//	//在栈上使用构造函数,永远不能显示地调用构造函数
//	SpreadsheetCell myCell5(5), anotherCell6(4);
//	cout << "cell 5: " << myCell5.getValue() << endl;
//	cout << "cell 6: " << anotherCell6.getValue() << endl;
//	//在堆上使用构造函数
//	SpreadsheetCell *myCell7 = new SpreadsheetCell(7);
//	SpreadsheetCell *anotherCell8 = nullptr;
//	anotherCell8 = new SpreadsheetCell(8);
//	cout << "cell 7: " << myCell7->getValue() << endl;
//	cout << "cell 8: " << anotherCell8->getValue() << endl;
//	delete myCell7;
//	myCell7 = nullptr;
//	delete anotherCell8;
//	anotherCell8 = nullptr;
//	//使用智能指针
//	shared_ptr<SpreadsheetCell> myCell9(new SpreadsheetCell(9));
//	shared_ptr<SpreadsheetCell> anotherCell10(new SpreadsheetCell());
//	cout << "cell 9: " << myCell9->getValue() << endl;
//	cout << "cell 10: " << anotherCell10->getValue() << endl;
//	//使用不同的构造函数
//	SpreadsheetCell myCell11("test");
//	SpreadsheetCell anotherCell12(4.4);
//	shared_ptr<SpreadsheetCell> myCell13(new SpreadsheetCell("4.4"));
//	cout << "cell 11: " << myCell11.getString() << endl;
//	cout << "cell 12: " << anotherCell12.getString() << endl;
//	cout << "cell 13: " << myCell13->getValue() << endl;
//	//在栈上使用默认构造函数
//	SpreadsheetCell myCell14;
//	myCell14.setValue(14);
//	cout << "cell 14: " << myCell14.getValue() << endl;
//	//按下面的方式使用默认构造函数是错误的
//	//SpreadsheetCell myCell15(); //编译器把这句话当作了函数声明
//	//myCell15.setValue(15);  //编译器不认识myCell15
//	//在堆中使用默认构造函数,可以使用也可以不用括号
//	shared_ptr<SpreadsheetCell> myCell16(new SpreadsheetCell());
//	//或shared_ptr<SpreadsheetCell> myCell16(new SpreadsheetCell());
//	cout << "cell 16: " << myCell16->getValue() << endl;
//
//	//显示调用复制构造函数
//	SpreadsheetCell myCell17(17);
//	SpreadsheetCell myCell18(myCell17);
//	cout << "cell 17: " << myCell17.getValue() << " " << myCell17.getString() << endl; 
//	cout << "cell 18: " << myCell18.getValue() << " " << myCell18.getString() << endl;
//
//	return 0;
//}

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