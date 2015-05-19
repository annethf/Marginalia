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

//�����ж�̬�����ڴ�ʱ�����ֻ�����ֹ�����˸��ƶ������Ϊ����ֵ��ֻ�轫��ֵ�����
//�Լ����ƹ��캯�����Ϊprivate��ͨ�����ַ������������κ��˰�ֵ���ݶ��󡢴Ӻ�������
//�������ض������Ϊ����ֵʱ�����������ᱨ��
//����Ĵ�������𵽽�ֹ����ֵ����ֵ���ݵ�����
//private: //����Ҫ�ṩprivate��ֵ���캯���Լ���ֵ�������ʵ�֡���������Զ����鿴���ǡ�
		 //��Ϊ���������������������ǡ��������������������ຯ������Ӧ��������������Ϊprotected, ������private
	//Spreadsheet(const Spreadsheet& src);
	//Spreadsheet& operator=(const Spreadsheet& rhs);
};

