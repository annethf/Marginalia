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

class PointSequence
{
public:
	PointSequence(initializer_list<double> args)
	{
		if (args.size() % 2 != 0)
		{
			throw invalid_argument("initializer_list should "
				"contain even number of elements.");
			for (auto iter = args.begin(); iter != args.end(); ++iter)
				mVecPoints.push_back(*iter);
		}
	}
	void dumpPoints() const
	{
		for (auto citer = mVecPoints.cbegin();
			citer != mVecPoints.cend(); citer += 2)
		{
			cout << "(" << *citer << ", " << *(citer + 1) << ")" << endl;
		}
	}

protected:
	vector<double> mVecPoints;
	//C++11�����ڶ������ʱ��ֱ�ӳ�ʼ����Ա������
	//��C++11֮ǰ��ֻ���ڹ��캯������ʼ����Ա�б��в��ܳ�ʼ����Ա����
	//���ң���C++11֮ǰ��ֻ��static const���γ�Ա�����������ඨ���г�ʼ��
	static const int kI1 = 1; //OK
	//Error ��C++11֮ǰ��ʹ��static const���͵ģ����������α�����Ҳ����������ʼ���� C++11Ҳ��֧�����ֳ�ʼ����ʽ
	//static const string kStr = "test"; 
	int mInt = 1;
	string mStr = "test";
};