#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

#if 0
char buff[1024]; sizeof(buff)
char * data;  sizeof(data)
#endif

class Base
{
public:
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

	Base & operator=(const Base & rhs)                         //基类重载operator= 复制语义
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
		cout << _pdata1 << endl;
	}
private:
	char * _pdata1;
};

//1. 当派生类没有显式定义复制控制函数，而基类有显式定义，
//则复制一个派生类对象时，会自动调用基类相应的复制控制函数
class Derived : public Base
{
public:
	Derived(const char * pdata)
	: Base(pdata)
	{
		cout << "Derived(const char *)" << endl;
	}
};

int main(void)
{
	Derived d1("hello,world");
	cout << "d1 = ";
	d1.display();

	Derived d2(d1);
	cout << "d2 = ";
	d2.display(); 
	cout << endl;

	Derived d3("shenzen");
	cout << "d3 = ";
	d3.display();
	cout << "d1 = ";
	d1 = d3;
	d1.display();

	return 0;
}
/*
总结:
派生类复制函数负责派生类的数据成员，基类复制函数只能负责基类部分的数据成员

1.如果用户定义了基类的拷贝构造函数，而没有定义派生类的拷贝构造函数，
那么在用一个派生类对象初始化新的派生类对象时，两对象间的派生类部分执行缺省的行为，而两对象间的基类部分执行用户定义的基类拷贝构造函数。

2.如果用户重载了基类的对象赋值运算符=，而没有定义派生类的对象赋值运算符，
那么在用一个派生类对象给另一个已经存在的派生类对象赋值时，两对象间的派生类部分执行缺省的赋值行为，而两对象间的基类部分执行用户定义的重载赋值函数

*/