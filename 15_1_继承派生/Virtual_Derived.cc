#include <iostream>
using std::cout;
using std::endl;


class A
{
public:
	A(int ix = 0)
	: _ix(ix)
	{}
	
	void setX(int ix)
	{	_ix = ix;	}

	void print() const
	{	cout << "A::_ix = " << _ix << endl;}

private:
	int _ix;
};

class B : virtual public A
{};

class C : virtual public A
{};

class D                //菱形继承 一旦初始化则存在两份A对象
: public B
, public C
{};

int main(void)
{
	D d;
	d.setX(1);			//解决存储二义性:采用虚继承
	d.print();
	
	return 0;
}
