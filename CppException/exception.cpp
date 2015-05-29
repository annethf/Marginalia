// C++异常

//最简单的异常处理
#include <stdexcept> //这个头文件包含invalid_argument类型的异常
int SafeDivide(int num, int den)
{
	if(den == 0)
		throw invalid_argument('Divide by zero."); //抛出异常
	return num / den;
}

int main()
{
	try
	{
		cout << SafeDivide(5, 2) << endl;
		cout << SafeDivide(10, 0) << endl; 
		cout << SafeDivide(3, 3) << endl;
	}cathch(const invalid_argument& e)
	{
		cout << "Caught exception: " << e.what() << endl; //捕获异常
	} 
	return 0;
}

//throw还可用于再次抛出当前异常
void go() { throw 2; }
void f()
{
	try
	{
		go();
	}catch(int i)
	{
		cout << Caugth in f: " << i << endl;
		throw; //再次抛出当前异常(即在go函数中抛出的异常)
	}
}

int main()
{
	try
	{
		f();
	}catch(int i)
	{
		cout << "Caught in main: " << i << endl; //捕获f函数再次抛出的异常
	}
	return 0;
}

//一个简单的例子
#include <exception> //包含exception类型的异常，事实上exception类是所有异常类的父类
#include <iostream>
#include <fstream>
void readIntegerFile(const string& fileName, vector<int>& dest)
{
	ifstream istr;
	int temp;
	istr.open(fileName.c_str());
	if(istr.fail())
		throw exception(); //这里不需要字符串，表明这个类有一个默认构造函数
	while(istr >> temp)
		dest.push_back(temp);
}

int main()
{
	vector<int> myInts;
	const string fileName = "IntegerFile.txt";
	try
	{
		readIntegerFile(fileName, myInts);
	}catch(const exception& e)
	{
		cerr << "Unable to open file " << fileName << endl;
		return 1;
	}
	for(size_t i = 0; i < myInts.size(); i++)
		cout << myInts[i] << " " ;
	cout << endl;
	return 0;
}

//C++允许抛出任意类型的异常，除了exception类型外，还可以抛出int(像第2个例子那样),double...
void readIntegerFile(const string& fileName, vector<int>& dest)
{
	ifstream istr;
	int temp;
	istr.open(fileName.c_str());
	if(istr.fail())
		throw 5;
	while(istr >> temp)
		dest.push_back(temp);
}

int main()
{
	vector<int> myInts;
	const string fileName = "IntegerFile.txt";
	try
	{
		readIntegerFile(fileName, myInts);
	}catch(int e)
	{
		cerr << "Unable to open file " << fileName << endl;
		return 1;
	}
	for(size_t i = 0; i < myInts.size(); i++)
		cout << myInts[i] << " ";
	cout << endl;
	return 0;
}

//除了int, double, exception(及其子类)之外，C++还允许抛出C风格字符串char*
void readIntegerFile(const string& fileName, vector<int>& dest)
{
	ifstream istr;
	int temp;
	istr.open(fileName.c_str());
	if(istr.fail())
		throw "Unable to open file.";
	while(istr >> temp)
		dest.push_back(temp);
}

int main()
{
	vector<int> myInts;
	const string fileName = "IntegerFile.txt";
	try
	{
		readIntegerFile(fileName, myInts);
	}catch(const char* e)
	{
		cerr << e << endl;
		return 1;
	}
	for(size_t i = 0; i < myInts.size(); i++)
		cout << myInts[i] << " ";
	cout << endl;
	return 0;
}

//C++虽然对异常抛出(如抛出int,double,exception(及其子类)等等都是可以的)
//和捕获的方式(可以按值捕获(即catch(exception e)、按引用捕获(即catch(exception& e))
//按const引用捕获(即catch(const exception& e))，甚至还可以按char*或const char*捕获)没有做严格限制；
//但是强烈建议抛出异常对象(int,doube等不算对象)、并按const引用捕获异常

//抛出并捕获多个异常
//简单处理
void readIntegerFile(const string& fileName, vector<int>& dest)
{
	ifstream istr;
	int temp;
	istr.open(fileName.c_str());
	if(istr.fail())
		throw exception();
	while(istr >> temp)
		dest.push_back(temp);
	
	if(istr.eof())
		istr.close();
	else
	{
		istr.close();
		throw exception();
	}
}

int main()
{
	vector<int> myInts;
	const string fileName = "IntegerFile.txt";
	try
	{
		readIntegerFile(fileName, myInts);
	}catch(const exception& e)
	{
		cerr << "Unable either to open or to read" << fileName << endl; 
		return 1;
	}
	for(size_t i = 0; i < myInts.size(); i++)
		cout << myInts[i] << " ";
	cout << endl;
	return 0;
}

//抛出不同类型的异常
#include <stdexcept>
void readIntegerFile(const string& fileName, vector<int>& dest)
{
	ifstream istr;
	int temp;
	if(istr.fail())
		throw invalid_argument(""); //构造函数的要求，参数必须是字符串
	while(istr >> temp)
		dest.push_back(temp);
	if(istr.eof())
		istr.close();
	else
	{
		istr.close();
		throw runtime_error("");
	}
}

int main()
{
	vector<int> myInts;
	const string fileName = "IntegerFile.txt";
	try
	{
		readIntegerFile(fileName, myInts);
	}catch(cosnt invalid_argument& e)
	{
		cerr << "Unable to open file" << fileName << endl;
		return 1;
	}catch(const runtime_error& e)
	{
		cerr << "Error reading file" << fileName << endl;
		return 1;
	}
	for(size_t i = 0; i < myInts.size(); i++)
		cout << myInts[i] << " ";
	cout << endl;
	return 0;
}

//匹配所有异常
#include <stdexcept>
void readIntegerFile(const string& fileName, vector<int>& dest)
{
	ifstream istr;
	int temp;
	if(istr.fail())
		throw invalid_argument(""); //构造函数的要求，参数必须是字符串
	while(istr >> temp)
		dest.push_back(temp);
	if(istr.eof())
		istr.close();
	else
	{
		istr.close();
		throw runtime_error("");
	}
}

int main()
{
	vector<int> myInts;
	const string fileName = "IntegerFile.txt";
	try
	{
		readIntegerFile(fileName, myInts);
	}catch(...) //"..."用来匹配所有异常
	{
		cerr << "Error reading or opening file" << fileName << endl;
		return 1;
	}
	for(size_t i = 0; i < myInts.size(); i++)
		cout << myInts[i] << " ";
	cout << endl;
	return 0;
}

//显示地匹配异常类型，并用“...”处理其他所有异常
#include <stdexcept>
void readIntegerFile(const string& fileName, vector<int>& dest)
{
	ifstream istr;
	int temp;
	if(istr.fail())
		throw invalid_argument(""); //构造函数的要求，参数必须是字符串
	while(istr >> temp)
		dest.push_back(temp);
	if(istr.eof())
		istr.close();
	else
	{
		istr.close();
		throw runtime_error("");
	}
}

//在异常抛出的时候，会按照在代码中的显示顺序查找catch处理程序。
int main()
{
	vector<int> myInts;
	const string fileName = "IntegerFile.txt";
	try
	{
		readIntegerFile(fileName, myInts);
	}catch(cosnt invalid_argument& e)
	{
		cerr << "Unable to open file" << fileName << endl;
		return 1;
	}catch(const runtime_error& e)
	{
		cerr << "Error reading file" << fileName << endl;
		return 1;
	}catch(...) //"..."用来匹配所有异常
	{
		cerr << "Other error!" << endl;
		return 1;
	}
	for(size_t i = 0; i < myInts.size(); i++)
		cout << myInts[i] << " ";
	cout << endl;
	return 0;
}
