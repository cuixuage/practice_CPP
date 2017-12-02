#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
/*
	一般来说，如果基类中定义了虚函数，基类析构函数也应被定义为虚析构函数，尤其是类内有申请的动态内存，需要清理和释放的时候。
	避免内存泄漏
	
	例如:避免new之后; delete pbase;			//根据对象内容执行对应的析构函数 而非根据指针phase的类型
*/
class Base
{
public:
	Base(const char * pbase)
	: _pbase(new char[strlen(pbase) + 1]())
	{
		cout << "Base(const char*)" << endl;
		strcpy(_pbase, pbase);
	}

	virtual
	~Base()
	{
		cout << "~Base()" << endl;
		delete [] _pbase;
	}

	virtual
	void display() const
	{
		cout << _pbase;
	}
private:
	char * _pbase;
};

class Child : public Base
{
public:
	Child(const char * pbase, const char * pchild)
	: Base(pbase)
	, _pchild(new char[strlen(pchild) + 1]())
	{
		cout << "Child()" << endl;
		strcpy(_pchild, pchild);
	}

	//一旦基类的析构函数成为虚函数之后，派生类的析构函数会自动成为虚函数
	//即使没有给出virtual关键字
	~Child()
	{
		cout << "~Child()" << endl;
		delete [] _pchild;
	}

	virtual
	void display()const
	{
		Base::display();
		cout << _pchild << endl;
	}

private:
	char * _pchild;
};


int main(void)
{
	Base * pbase = new Child("hello,", "world");     	//基类指针指向 子类对象

	pbase->display();

	delete pbase;			//我们需要调用的是派生类的析构函数
	
	//如果基类的析构函数不是virtual 那么这里只会调用基类的析构函数
	
	//指针类型为Base ,但是构造函数为virtual ,所以会调用执行实际指向对象的析构函数
}



/*
output:
Base(const char*)				//先执行基类构造函数(析构函数是virtual)
Child()
hello,world
~Child()						//执行子类析构  虽然此时delete是Base类型的指针 child对象内容
~Base()
*/

