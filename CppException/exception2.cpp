//内存分配错误
//产品代码中必须为内存分配错误负责，所以正确的new看起来应该是这样的

try
{
	ptr = new int[numInts];
}catch(const bad_alloc& e)
{
	cerr << __FILE__ "( " << __LINE__ << "): Unable to allocate memory! " << endl;
	return;
}

//默认情况下new和new[]的行为是抛出bad_alloc类型的异常，这个类型在<new>头文件中定义。

//不抛出异常的new
ptr = new(nothrow) int[numInts];
if(ptr == nullptr)
{
	cerr << __FILE__ "( " << __LINE__ << "): Unable to allocate memory! " << endl;
	return;
}
//C++提供了new和new[]的nothrow版本，如果内存分配失败将返回nullptr而不是抛出异常。
//除此之外，用户还可以定制自己的内存分配失败行为，因为定制new_handler比较复杂，建议慎用。

//构造函数中的错误
//虽然构造函数没有返回值，但是可以抛出异常。不过需要注意的是：构造函数在抛出异常之后，
//析构函数将不被执行；因此在异常离开构造函数之前，必须仔细清理所有资源，并释放构造函数
//中分配的所有内存。

#include <stdexcept>
#include "Element.h"
class Matrix
{
	public:
		Matrix(unsigned int width, unsigned int height) throw(std::bad_alloc);
		virtual ~Matrix();
	protected:
		unsigned int mWidth;
		unsigned int mHeight;
		Element** mMatrix;
};

class Element
{
	protected:
		int mValue;
};

Matrix::Matrix(unsigned int width, unsigned int height) throw(bad_alloc)
		:mWidth(width), mHeight(height), mMatirx(nullptr)
{
	mMatrix = new Element*[width];
	unsigned int i = 0;
	try
	{
		for(i = 0; i < height; i++)
			mMatrix[i] = new Element[height];
	}catch(...)
	{
		for(unsigned int j = 0; j < i; j++)
			delete [] mMatrix[j];
		delete [] mMatirx;
		mMatrix = nullptr;
		throw bad_alloc();
	}
}

Matrix::~Matrix()
{
	for(unsigned int i = 0; i < height; i++)
		delete [] mMatirx[i];
	delete [] mMatrix;
	mMatrix = nullptr;
}

//另外一个问题，如果使用了继承，父类的构造函数先于子类的构造函数被调用；
//如果子类的构造函数抛出异常，如何释放父类构造函数分配的资源？
//C++保证会运行任何构造完整“字对象”的析构函数，因此，任何没发生异常的
//构造函数所对应的析构函数都会运行。

//在构造函数列表中抛出异常(构造函数的function-try-blocks)

class SubObject
{
	public:
		SubObject(int i) throw(std::runtime_error);
};

SubObject::SubObject(int i) throw(runtime_error)
{
	throw std::runtime_error("Exception by SubObject ctor.");
}

class MyClass
{
	public:
		MyClass() throw(std::runtime_error);
	protected:
		SubObject mSubObject;
};

MyClass::MyClass() throw(std::runtime_error)
try
	:mSubObject(42)
{
	/*... constructor body ...*/
}
catch(const std::exception& e)
{
	cout << "function-try-block caught: " << e.what() << endl; //没有抛出新异常
}

int main()
{
	try
	{
		MyClass m;
	}catch(const std::exception& e)
	{
		cout << "main() caught: " << e.what() << endl;
	}
	return 0;
}

//构造函数function-try-block中的catch块中必须重新抛出新异常或者抛出
//当前异常，上面的示例中catch没有显示抛出新异常，C++会自动抛出当前异常。

//不应该让析构函数抛出任何异常。