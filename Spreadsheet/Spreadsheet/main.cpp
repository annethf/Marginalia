#include "stdafx.h"
#include "SpreadsheetCell.h"
#include <iostream>
#include <memory>

using namespace std;

int main(int argc, char *argv)
{
	SpreadsheetCell myCell1, anotherCell2;
	myCell1.setValue(6);
	anotherCell2.setString("3.2");
	cout << "cell 1: " << myCell1.getValue() << endl;
	cout << "cell 2: " << anotherCell2.getValue() << endl;
	//��ָͨ��
	//C++��new���г�ʼ���Ĺ��ɣ�
	//�����й��캯�����࣬������û�����ţ����ù��캯�����г�ʼ����
	//���û�й��캯�����򲻼����ŵ�newֻ�����ڴ�ռ䣬�������ڴ�ĳ�ʼ��
	//���������ŵ�new���ڷ����ڴ��ͬʱ��ʼ��Ϊ0
	SpreadsheetCell* myCell3 = new SpreadsheetCell();
	//��SpreadsheetCell* myCellp = new SpreadsheetCell();
	myCell3->setValue(3.7);
	cout << "cellp 3: " << myCell3->getValue() << " "
		<< myCell3->getString() << endl;
	delete myCell3;
	myCell3 = nullptr;
	//����ָ��(C++11)
	shared_ptr<SpreadsheetCell> myCell4(new SpreadsheetCell());
	myCell4->setValue(3.7);
	cout << "cell 3: " << myCell4->getValue() << " cell 4: "
		<< myCell4->getString() << endl;
	//��ջ��ʹ�ù��캯��,��Զ������ʾ�ص��ù��캯��
	SpreadsheetCell myCell5(5), anotherCell6(4);
	cout << "cell 5: " << myCell5.getValue() << endl;
	cout << "cell 6: " << anotherCell6.getValue() << endl;
	//�ڶ���ʹ�ù��캯��
	SpreadsheetCell *myCell7 = new SpreadsheetCell(7);
	SpreadsheetCell *anotherCell8 = nullptr;
	anotherCell8 = new SpreadsheetCell(8);
	cout << "cell 7: " << myCell7->getValue() << endl;
	cout << "cell 8: " << anotherCell8->getValue() << endl;
	delete myCell7;
	myCell7 = nullptr;
	delete anotherCell8;
	anotherCell8 = nullptr;
	//ʹ������ָ��
	shared_ptr<SpreadsheetCell> myCell9(new SpreadsheetCell(9));
	shared_ptr<SpreadsheetCell> anotherCell10(new SpreadsheetCell);
	cout << "cell 9: " << myCell9->getValue() << endl;
	cout << "cell 10: " << anotherCell10->getValue() << endl;
	//ʹ�ò�ͬ�Ĺ��캯��
	SpreadsheetCell myCell11("test");
	SpreadsheetCell anotherCell12(4.4);
	shared_ptr<SpreadsheetCell> myCell13(new SpreadsheetCell("4.4"));
	cout << "cell 11: " << myCell11.getString() << endl;
	cout << "cell 12: " << anotherCell12.getString() << endl;
	cout << "cell 13: " << myCell13->getValue() << endl;
	//��ջ��ʹ��Ĭ�Ϲ��캯��
	SpreadsheetCell myCell14;
	myCell14.setValue(14);
	cout << "cell 14: " << myCell14.getValue() << endl;
	//������ķ�ʽʹ��Ĭ�Ϲ��캯���Ǵ����
	//SpreadsheetCell myCell15(); //����������仰�����˺�������
	//myCell15.setValue(15);  //����������ʶmyCell15
	//�ڶ���ʹ��Ĭ�Ϲ��캯��,����ʹ��Ҳ���Բ�������
	shared_ptr<SpreadsheetCell> myCell16(new SpreadsheetCell);
	//��shared_ptr<SpreadsheetCell> myCell16(new SpreadsheetCell());
	cout << "cell 16: " << myCell16->getValue() << endl;

	return 0;
}