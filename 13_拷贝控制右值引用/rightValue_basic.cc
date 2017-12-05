#include <string.h>
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

//复制语义  形参 const T &
//移动语义  形参 T &&       (往往加上 noexcept)
//区别:拷贝构造函数/移动构造函数   拷贝赋值运算符/移动赋值运算符

class String
{
public:
	String()
	: _pstr(new char[1])
	{}															//无参\有参的构造函数
	String(const char * pstr)
	: _pstr(new char[strlen(pstr) + 1]())
	{
		cout << "String(const char * )" << endl;
		strcpy(_pstr, pstr);
	}															//具有复制语义//复制构造函数
	String(const String & rhs)
	: _pstr(new char[strlen(rhs._pstr) + 1]())
	{
		strcpy(_pstr, rhs._pstr);
		cout << "String(const String&)" << endl;
	}
	
#if 1														//移动构造函数  rhs右值对象
															//不分配任何新内存
	String(String && rhs)  noexcept
	: _pstr(rhs._pstr) 										//浅拷贝
	{
		rhs._pstr = NULL;									//右值对象的资源指针=NULL
		cout << "移动语义 constructor String(String && rhs)" << endl;
	}
#endif	
															//复制语义 赋值运算符函数
															//左值对象开辟新空间 深拷贝
	String & operator=(const String & rhs)
	{
		cout << "String & operator=(const String &rhs)" << endl;
		if(this != & rhs)
		{
			delete [] _pstr;
			_pstr = new char[strlen(rhs._pstr) + 1]();
			strcpy(_pstr, rhs._pstr);
		}
		return *this;
	}
	
#if 1														//具有移动语义的函数会优先执行？	//移动赋值运算符函数
															//浅拷贝 
	String & operator=(String && rhs) noexcept
	{
		if(this != &rhs)
		{
			cout << "移动语义  String & operator=(String && rhs)" << endl;
			delete [] _pstr;
			_pstr = rhs._pstr;
			rhs._pstr = NULL;
		}
		
		return *this;
	}
#endif

	~String()
	{
		delete [] _pstr;
		cout << "~String()" << endl;
	}

	friend std::ostream & operator<<(std::ostream & os, const String & rhs);

private:
	char * _pstr;
};

String && func()
{ 
						 //这里会被警告  返回了一个不再存在的实例
	// return "hello!";     //返回右值对象  参数值传递的函数返回 右值对象 即将被销毁
}

std::ostream & operator<<(std::ostream & os, const String & rhs)
{
	os << rhs._pstr;
	return os;
}

int test0(void)
{
	vector<String> vec;
	vec.reserve(32);
	vec.push_back("hello, world");	
	return 0;
}

int test1()
{

	String s1("hello");								//有参 const char* 构造函数
	String s2("world");
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;

	s1 = "world_2";									//右值 char*=》 str=》移动语义的赋值运算符 =》析构"world"对象

	// String s4(std::move(s1));     					//右值构造函数
	// cout << "s1 = " << s1 << endl;					//s1 资源窃取 无法输出

	s1 = s2;										//复制语义 拷贝赋值运算符   //编译器会识别参数左值还是右值  
	cout<<s1<<endl;
	
	return 0;
}

int main(void)
{
	//test0();
	
	//test1();
	
	//String && ref = func();
	//cout<<ref<<endl;
	
	return 0;
}

/*
test0 output:
String(const char * )							//"hello world"构造成str
移动语义 constructor String(String && rhs)		
~String()
~String()
*/
