#include <string>
using std::string;

class SpreadsheetCell
{
public:
	SpreadsheetCell(){} //��ʽ��Ĭ�Ϲ��캯��
	//C++11��ʾĬ�Ϲ��캯�������������ڹ��еĽӿ��ļ���ʵ���κη���
	//SpreadsheetCell() = default; 
	//����붨��һ���࣬���������û���κι��캯��
	//���Ҳ����ñ������Զ�����Ĭ�Ϲ��캯������ô����
	//ʹ����ʾɾ�����캯��(explicitly deleted constructors)
	//SpreadsheetCell() = delete;
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(string initialValue);
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