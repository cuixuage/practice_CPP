#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::bind;
using std::function;

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

//  int(int,int)   -->  函数标签
//  typedef int (* Function)(int, int)  例如:Function f1  Function是f1的类型
//  function<int(int, int)> f1;  

//********************************************************std::bind 基本使用 绑定自由函数
int test0()
{
	//bind提前绑定参数时，未提前绑定的参数所在的位置需要使用占位符占住
	//bind 生成可调用对象f1  ; f1实际调用func
	auto f1 = bind(func, 10, std::placeholders::_1);
	cout << f1(20) << endl;

	auto f2 = bind(func, 10, 11);
	cout << f2() << endl;
	return 0;
}

//***************************************************************std::bind 绑定其它类的成员函数  
//区别: 成员函数的引用传递   参数而外需要 *this   
int test1()
{
	Foo foo;
	//如果bind要绑定成员函数，要在前面加上取地址符号&。 第二个参数是调用对象的地址
	auto f1 = bind(&Foo::add, &foo, 10, std::placeholders::_1);
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
void test2()
{
	using namespace std::placeholders;								//指定std::placeholders

	int n = 7;
	// bind绑定参数时，采用的是值传递, 会进行复制
	//如果我们希望传递bind的参数对象而又不拷贝它,使用std::ref() 或者 std::cref()

	auto f1 = bind(display, _3, _1, 42, std::cref(n), n);			//最后一个参数n是值传递,以后固定为数值 7
	n = 10;
	f1(11, 22, 33, 44,55,66,77);									//实际调用 display(33,11,42,10,7)		//注意ref cref传递地址。
	//此处output: (33,11,42,10,7)
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
	// test0();
	// test1();
	//test2();
	//test4();

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
    auto f1 = std::bind(f, _2, _1, 42, std::cref(n), n);                        //变量n的地址传递(ref)   || bind默认为值传递,会将其参数拷贝一个副本
    n = 10;
    f1(1, 2, 1001); // 1 is bound by _1, 2 is bound by _2, 1001 is unused
                    // makes a call to f(2, 1, 42, n, 7)						//ref cref传递地址  ; 但是最后一个参数还是7不变
 
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

Output:
2 1 42 10 7
12 12 12 4 5
1 5 0 2 0 8 2 2 10 8
100
10
10
10

***************************************************************************/

/************************************cref 与 ref区别
#include <functional>
#include <iostream>
 
void f(int& n1, int& n2, const int& n3)
{
    std::cout << "In function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    ++n1; // 增加存储于函数对象的 n1 副本
    ++n2; // 增加 main() 的 n2
    // ++n3; // 编译错误
}
 
int main()
{
    int n1 = 1, n2 = 2, n3 = 3;
    std::function<void()> bound_f = std::bind(f, n1, std::ref(n2), std::cref(n3));
    n1 = 10;
    n2 = 11;
    n3 = 12;
    std::cout << "Before function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    bound_f();
    std::cout << "After function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
}
输出：
Before function: 10 11 12
In function: 1 11 12
After function: 10 12 12
******************************************************/
