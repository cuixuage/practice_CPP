#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
//基类
class Base
{
public:
	Base()
	: _pdata1(new char[1]())
	{
		cout << "Base()" << endl;
	}

	Base(const char * pdata1)
	: _pdata1(new char[strlen(pdata1) + 1]())
	{
		cout << "Base(const char *)" << endl;
		strcpy(_pdata1, pdata1);
	}

	Base(const Base & rhs)
	: _pdata1(new char[strlen(rhs._pdata1) + 1]())
	{
		cout << "Base(const Base &)" << endl;
		strcpy(_pdata1, rhs._pdata1);
	}

	Base & operator=(const Base & rhs)
	{
		cout << "Base & operator=(const Base&)" << endl;
		if(this != &rhs)
		{
			delete [] _pdata1;
			_pdata1 = new char[strlen(rhs._pdata1) + 1]();
			strcpy(_pdata1, rhs._pdata1);
		}
		return *this;
	}

	~Base()
	{
		delete [] _pdata1;
		cout << "~Base()" << endl;
	}

	void display() const
	{
		cout << "Base:" << _pdata1 << endl;
	}
private:
	char * _pdata1;
};

//2. 当派生类有显式定义复制控制函数，而基类有显式定义，
//则复制一个派生类对象时，不会自动调用基类相应的复制控制函数,
//必须手动显式调用基类的相应复制控制函数
class Derived : public Base
{
public:
	Derived(const char * pdata1, const char * pdata2)
	: Base(pdata1)
	, _pdata2(new char[strlen(pdata2) + 1]())
	{
		cout << "Derived(const char *)" << endl;
		strcpy(_pdata2, pdata2);
	}

	Derived(const Derived & rhs)
	: Base(rhs) //必须加上
	, _pdata2(new char[strlen(rhs._pdata2) + 1]())
	{
		strcpy(_pdata2, rhs._pdata2);
		cout << "Derived(const Derived &)" << endl;
	}

	Derived & operator=(const Derived & rhs)
	{
		cout << "Derived & operator=(const Derived & rhs)" << endl;
		if(this != &rhs)
		{
			Base::operator=(rhs);					//必须加上  手动显式调用基类的相应拷贝移动函数
													//这也是 派生类Derived对象向上转型为基类Base对象去初始化基类部分成员
													
			delete [] _pdata2;
			_pdata2 = new char[strlen(rhs._pdata2) + 1]();
			strcpy(_pdata2, rhs._pdata2);
		}
		return *this;
	}


	~Derived()
	{
		delete [] _pdata2;
	}
	void display() const
	{
		Base::display();
		cout << "Derived:" << _pdata2 << endl;
	}
private:
	char * _pdata2;
};

int main(void)
{
	Derived d1("hello,", "world");					//d1
	cout << "d1 = ";
	d1.display();
	cout << endl;

	Derived d2(d1);									//派生复制构造函数
	cout << "d2 = ";
	d2.display(); 
	cout << endl << endl;

#if 1
	Derived d3("shenzen,", "wangdao");
	cout << "d3 = ";
	d3.display();
	cout << "d1 = ";
	cout << endl;
	d1 = d3;										//派生类对象的复制		//两次复制：基类+派生类(分别进行移动基类\派生类的数据成员)
	d1.display();
#endif

	return 0;
}
/*
	如果用户定义了派生类的拷贝构造函数或者重载了派生类的对象赋值运算符=，则在用已有派生类对象初始化新的派生类对象时，或者在派生类对象间赋值时，	
	将会执行用户定义的派生类的拷贝构造函数或者重载赋值函数，而不会再自动调用基类的拷贝构造函数和基类的重载对象赋值运算符，
	这时，通常需要用户在派生类的拷贝构造函数或者派生类的赋值函数中显式调用基类的拷贝构造或赋值运算符函数。

*/