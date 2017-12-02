#include <iostream>
using std::cout;
using std::endl;

#if 1
class A
{//拥有纯虚函数的类就是一个接口类
public:
	//拥有纯虚函数的类是一个抽象类，抽象类是不能创建对象的
	virtual void display()=0;
	virtual void print()=0;
};


#endif
class B
: public A
{// 当派生类继承自抽象类，必须要实现基类所有的纯虚函数，才能够创建对象
 // 只要有一个纯虚函数没有实现，其依然是一个抽象类
public:
	void display()
	{
		cout << "B::display()" << endl;
	}
};

class C : public B
{
public:
	void print()
	{
		cout << "C::print()" << endl;
	}
};

int main(void)
{
	//A a;//ERROR
	
	//A * p = new B;
	//p->display();

	cout << "sizeof(B) = " << sizeof(B) << endl;				//8bytes 虚函数入口地址指针大小   ; 纯虚函数不占位置(因为其是接口类,纯虚函数是未实现函数 不在虚函数表中) 
	cout << "sizeof(C) = " << sizeof(C) << endl;

	A * p = new C;
	p->display();
	p->print();

	return 0;
}

/*
output:
sizeof(B) = 8
sizeof(C) = 8
B::display()
C::print()

*/