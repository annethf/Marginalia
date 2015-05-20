#include "SpreadsheetCell.h"

//ǰ������ forward declaration
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
	static const int kMaxHeight = 100; //��̬�������ݳ�Ա
	static const int kMaxWidth = 100;

protected:
	bool inRange(int val, int upper);
	int mWidth, mHeight;
	SpreadsheetCell** mCells;
	//�������ݳ�Ա���ڳ�ʼ���б��г�ʼ��
	SpreadsheetApplication& mTheApp;
	//C++11�еľ�̬���ݳ�Ա
	//static int sCounter = 0; //��仰���±�׼����֧�ֵģ����������ڲ���ʼ����̬���ݳ�Ա�����ɱ�׼��
							 //��̬���ݳ�Ա��Ҫ��������г�ʼ��
	int mId = 0; //C++11֧�����ڳ�ʼ��

//�����ж�̬�����ڴ�ʱ�����ֻ�����ֹ�����˸��ƶ������Ϊ����ֵ��ֻ�轫��ֵ�����
//�Լ����ƹ��캯�����Ϊprivate��ͨ�����ַ������������κ��˰�ֵ���ݶ��󡢴Ӻ�������
//�������ض������Ϊ����ֵʱ�����������ᱨ��
//����Ĵ�������𵽽�ֹ����ֵ����ֵ���ݵ�����
//private: //����Ҫ�ṩprivate��ֵ���캯���Լ���ֵ�������ʵ�֡���������Զ����鿴���ǡ�
		 //��Ϊ���������������������ǡ��������������������ຯ������Ӧ��������������Ϊprotected, ������private
	//Spreadsheet(const Spreadsheet& src);
	//Spreadsheet& operator=(const Spreadsheet& rhs);
};

