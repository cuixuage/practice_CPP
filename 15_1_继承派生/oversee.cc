#include <iostream>
using std::cout;
using std::endl;


class A
{
public:
	virtual void func(int x)
	{
		cout << "A::func(int)  x " << x << endl;
	}
};


class B
: public A
{
public:
	void func(const char * s)
	{
		cout << "B::func(const char *) " << s << endl;
	}

	virtual void func(int x)
	{	
		cout << "B::func(int) x " << x << endl;
	}

};

int main(void)
{
	B b;
	//b.func(10);//error
	b.func("hello");
	b.func(10);//调用方式是对象，发生的是隐藏

	A * p = new B;
	p->func(10);//覆盖

	return 0;
}



/**************************************
1.overload
只有在同一类定义中的同名成员函数才存在重载关系
class A
{
……
virtual int fun();
void fun(int);
void fun(double,double);
……
}

2.override
派生类中覆盖基类中的同名函数，要求两个函数的参数个数、参数类型、返回类型都相同，且基类函数必须是虚函数

3.oversea
隐藏指的是在某些情况下，派生类中的函数屏蔽了基类中的同名函数，这些情况包括：
2个函数参数相同，但基类函数不是虚函数。和覆盖的区别在于基类函数是否是虚函数。
2个函数参数不同，无论基类函数是否是虚函数，基类函数都会被屏蔽

*/