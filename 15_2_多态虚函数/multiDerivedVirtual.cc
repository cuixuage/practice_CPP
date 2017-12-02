#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;


class A
{
public:
	virtual void a(){	cout << "A::a()" << endl;	}					//同一个类多个虚函数 只保存一个虚函数表的入口地址
	virtual void b(){	cout << "A::b()" << endl;	}
	virtual void c(){	cout << "A::c()" << endl;	}
private:
	double _dx;
};

class B
{
public:
	virtual void a(){	cout << "B::a()" << endl;	}
	virtual void b(){	cout << "B::b()" << endl;	}
	void c(){	cout << "B::c()" << endl;	}
	void d(){	cout << "B::d()" << endl;	}
private:
	double _dy;
};


class C
: public A
, public B
{
public:
	virtual void a(){	cout << "C::a()" << endl;	}            //注意!多态特性

	void c(){	cout << "C::c()" << endl;	}					//同名函数 自动也是virtual 多态
	void d(){	cout << "C::d()" << endl;	}
private:
	double _dz;
};

int main(void)
{
	cout << "sizeof(A) = " << sizeof(A) << endl;     //16bytes = 8 bytes(vfptr) + 8 double
	cout << "sizeof(B) = " << sizeof(B) << endl;     //16bytes = 8 bytes(vfptr) + 8 double
	cout << "sizeof(C) = " << sizeof(C) << endl;     //40bytes = 16 A + 16 B + 8 double   

	A a;
	B b;
	C c;
	
	c.a();
	//c.b();//error,二义性      //c.A::b() or c.B::b()
	c.c();
	c.d();
	cout << endl;
	
	A * pA = &c;
	pA->a();//虚函数 C::a()              //多态性
	pA->b();//虚函数 A::b()
	pA->c();//虚函数 C::c()
	printf("pA = %p\n", pA);
	cout << endl;

	B * pB = &c;
	printf("pB = %p\n", pB);
	pB->a();//虚函数 C::a()
	pB->b();//虚函数 B::b()
	pB->c();//非虚函数 B::c()
	pB->d();//非虚函数 B::d()
	cout << endl;

	C * pC = &c;
	printf("pC = %p\n", pC);
	pC->a();// C::a()
	//pC->b();//error
	pC->c();// C::c()
	pC->d();// C::d()

	
	return 0;
}

/*
outpit:
sizeof(A) = 16
sizeof(B) = 16
sizeof(C) = 40
C::a()
C::c()
C::d()

C::a()
A::b()
C::c()
pA = 0x7ffdff8ed930

pB = 0x7ffdff8ed940
C::a()
B::b()
B::c()
B::d()

pC = 0x7ffdff8ed930
C::a()
C::c()
C::d()
*/
