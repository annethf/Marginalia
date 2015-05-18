#include <iostream>
#include <string>
#include <initializer_list>
#include <vector>
using std::string;
using std::endl;
using std::cout;
using std::initializer_list;
using std::invalid_argument;
using std::vector;

class SpreadsheetCell
{
public:
	SpreadsheetCell(){} //��ʽ��Ĭ�Ϲ��캯��
	//c++11��ʾĬ�Ϲ��캯�������������ڹ��еĽӿ��ļ���ʵ���κη���
	//SpreadsheetCell() = default; 
	//����붨��һ���࣬���������û���κι��캯��
	//���Ҳ����ñ������Զ�����Ĭ�Ϲ��캯������ô����
	//ʹ����ʾɾ�����캯��(explicitly deleted constructors)
	//SpreadsheetCell() = delete;
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(string initialValue);
	//���ƹ��캯�� copy constructor
	SpreadsheetCell(const SpreadsheetCell &src);
	//ί�й��캯��������Դ�����const����
	SpreadsheetCell(const string& initialValue);
	//��ֵ�����(����)������Դ�����const���ã��䷵��ֵ�Ǳ����ö��������
	SpreadsheetCell& operator=(const SpreadsheetCell& rhs);
	//������ʾ��Ĭ�ϻ���ɾ�����������ɵĸ�ֵ�����
	/*SpreadsheetCell& operator=(const SpreadsheetCell& rhs) = default;
	SpreadsheetCell& operator=(const SpreadsheetCell& rhs) = delete;*/
	void setValue(double inValue);
	double getValue() const;
	void setString(string inString);
	string getString() const;
protected:
	string doubleToString(double inValue) const;
	double stringToDouble(string inString) const;
	double mValue;
	string mString;
};
