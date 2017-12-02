#include <iostream>
using std::cout;
using std::endl;

//目的:多态    例如:不同类型对象调用同一函数(此函数内部使用重定义的虚函数)，从而返回值不同
//virtual具体调用取决于指针所指对象的类型——》传递不同派生类对象调用的display函数不同

class Base
{
public:
	virtual 
	int func(int x)
	{
		cout << "Base::func(int) x = " << x << endl; 
		return 0;
	}
private:
	double _dx;
};

class Sub
: public Base
{
public:
#if 1
	//virtual
	int func(int x)							//派生类类内virtual 覆盖基类相同的虚函数
	{
		cout << "Sub::func(int) x = " << x << endl;
		return x;
	}
#endif

	virtual 
	int func()  //它是Sub的一个新虚函数  	//参数个数类型不同于基类
	{
		return 0;
	}
private:
	double _dy;
};

/*
动态多态（虚函数机制）被激活的条件：
1. 基类要定义一个虚函数
2. 派生类要覆盖该虚函数
3. 基类的指针或者引用指向派生类对象
4. 该指针或引用调用虚函数
*/

void display(Base * pbase)
{
	pbase->func(10);
}

void print(Base & base)
{
	base.func(1);
}

/*
1.基类指针能够指向派生类对象   只是指针类型不同而已
2.基类的引用指向派生类对象
*/
int test0(void)
{
	Base base;
	Sub sub;
	display(&base);
	display(&sub);				//调用派生类 display
	return 0;
}

int test1()
{
	Base base;
	Sub sub;
	print(base);
	print(sub);					//调用派生类 display
	return 0;
}

int main(void)
{
	cout << "sizeof(Base) = " << sizeof(Base) << endl;           //16bytes = vfptr指针8bytes(64位) + double 8bytes
	cout << "sizeof(Sub) = " << sizeof(Sub) << endl;             //24bytes = 16(基类) + double 8bytes

	test0();
	cout<<endl;
	test1();
	
	return 0;
}
