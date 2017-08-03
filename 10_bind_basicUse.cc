#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::bind;
using std::function;

//     int(int,int)   -->  函数标签
//  typedef int (* Function)(int, int)
//  function<int(int, int)> f1;  

int func(int x, int y)
{
	return x + y;
}

struct Foo
{
	Foo()
	: _x(10)
	{}
	int add(int x, int y)
	{
		return x + y;
	}

	int _x;
};
//********************************************************std::bind 基本使用 绑定自由函数
int test0()
{
	//bind提前绑定参数时，未提前绑定的参数所在的位置需要使用占位符占住
	auto f1 = bind(func, 10, std::placeholders::_1);
	cout << f1(20) << endl;

	auto f2 = bind(func, 10, 11);
	cout << f2() << endl;
	return 0;
}
//*********************************************************掌握typedef定义类型 C 函数指针使用   
int test1()
{
	typedef int(*Function)(int,int);
	Function f = func;            //回调函数的注册
	cout << f(1, 2) << endl;

	return 0;
}
//***************************************************************std::bind 绑定其它类的成员函数  
//区别: 成员函数的引用传递   参数而外需要 *this   
int test2()
{
	//这种赋值的方式可以看成是：回调函数的注册
	//可以把function看成是函数类型的容器
	function<int(int)> f1 = bind(func, 10, std::placeholders::_1);
	//cout << f1(20) << endl;

	Foo foo;
	//如果bind要绑定成员函数，要在前面加上取地址符号&
	f1 = bind(&Foo::add, &foo, 10, std::placeholders::_1);
	cout << f1(20) << endl;

	//function<int()> f2 = bind(func, 10, 11);                     //auto 类型更方便
	auto f2 = bind (func,10,11);
	cout << f2() << endl;
	return 0;
}

void display(int n1, int n2, int n3, const int & n4, int n5)
{
	cout << "(" << n1 
		 << "," << n2
		 << "," << n3
		 << "," << n4
		 << "," << n5
		 << ")" << endl;
}
//*************************************************std::bind  占位符std::placeholders::_1的使用
void test3()
{
	using namespace std::placeholders;

	int n = 7;
	//function<void(int,int)> f1 = bind(display, _2, _1, 42, std::cref(n), n);
	//1. bind的占位符所在的位置代表的是形参的位置,
	//2. 占位符本身的数字代表的是实参传递时要绑定的实参的位置
	//3. bind绑定参数时，采用的是值传递, 会进行复制, 
	//   所以在绑定成员函数时，第一个参数尽量用对象的地址传递
	//4. 如果采用auto关键字接收bind的返回值，实参传递时个数不
	//   受限制, 多余的实参是无效参数

	auto f1 = bind(display, _3, _1, 42, std::cref(n), n);
	n = 10;
	f1(11, 22, 1001, 1002, 1003, 1004);
}
//**************************************************std::bind 绑定到数据成员
void test4()
{
	//bind除了能够绑定到普通函数，成员函数以外，
	//还能绑定到数据成员上
	Foo foo;
	auto f1 = bind(&Foo::_x, &foo);
	//int f1 = bind(&Foo::_x, &foo);
	cout << f1() << endl;
}


int main(void)
{
	//test0();
	//test1();
	//test2();
	//test3();
	test4();

	return 0;
}


/*******************http://en.cppreference.com*****************example

#include <random>
#include <iostream>
#include <memory>
#include <functional>
 
void f(int n1, int n2, int n3, const int& n4, int n5)
{
    std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}
 
int g(int n1)
{
    return n1;
}
 
struct Foo {
    void print_sum(int n1, int n2)
    {
        std::cout << n1+n2 << '\n';
    }
    int data = 10;
};
 
int main()
{
    using namespace std::placeholders;  // for _1, _2, _3...
 
    // demonstrates argument reordering and pass-by-reference
    int n = 7;
    // (_1 and _2 are from std::placeholders, and represent future
    // arguments that will be passed to f1)
    auto f1 = std::bind(f, _2, _1, 42, std::cref(n), n);                        //变量n 的引用测试  =》 bind 默认为值传递
    n = 10;
    f1(1, 2, 1001); // 1 is bound by _1, 2 is bound by _2, 1001 is unused
                    // makes a call to f(2, 1, 42, n, 7)
 
    // nested bind subexpressions share the placeholders
    auto f2 = std::bind(f, _3, std::bind(g, _3), _3, 4, 5);                      //嵌套bind
    f2(10, 11, 12); // makes a call to f(12, g(12), 12, 4, 5);
 
    // common use case: binding a RNG with a distribution
    std::default_random_engine e;
    std::uniform_int_distribution<> d(0, 10);
    std::function<int()> rnd = std::bind(d, e); // a copy of e is stored in rnd   //也可以使用  auto funcname = std::bind(~~~~)
    for(int n=0; n<10; ++n)
        std::cout << rnd() << ' ';
    std::cout << '\n';
 
    // bind to a pointer to member function
    Foo foo;
    auto f3 = std::bind(&Foo::print_sum, &foo, 95, _1);                            //bind 绑定到其他类函数指针(成员函数)
    f3(5);
 
    // bind to a pointer to data member                                             //bind 绑定到其他类数据成员
    auto f4 = std::bind(&Foo::data, _1);                    
    std::cout << f4(foo) << '\n';
 
    // smart pointers can be used to call members of the referenced objects, too
    std::cout << f4(std::make_shared<Foo>(foo)) << '\n'
              << f4(std::make_unique<Foo>(foo)) << '\n';
}

***************************************************************************/
