#include <iostream>
using std::cout;
using std::endl;

class A
{
public:
	void print() const
	{ cout << "A::print() " << endl;}
};

class B
{
public:
	void print() const
	{ cout << "B::print() " << endl;}
};

class C 
: public A
, public B
{
public:
	void show() const
	{	cout << "C::show()" << endl;}
};
							//多基派生 成员名二义性
int main(void)
{
	C c;
	//c.print();			//成员名冲突的二义性
	c.A::print();			//解决方案：作用域限定符
	c.B::print();
	c.show();
	return 0;
}
