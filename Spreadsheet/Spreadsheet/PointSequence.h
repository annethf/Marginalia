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
	//C++11允许在定义类的时候直接初始化成员变量，
	//在C++11之前，只有在构造函数体或初始化成员列表中才能初始化成员变量
	//而且，在C++11之前，只有static const整形成员变量才能在类定义中初始化
	static const int kI1 = 1; //OK
	//Error 在C++11之前即使是static const类型的，但不是整形变量，也不能这样初始化； C++11也不支持这种初始化方式
	//static const string kStr = "test"; 
	int mInt = 1;
	string mStr = "test";
};