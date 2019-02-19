#include <iostream>
#include <string.h>    //包含对于字符串的处理函数
using std::cout;
using std::endl;
/*
1.拷贝构造函数 copy constructor,为什么传递引用? (避免无限递归,形参传递是copy value)
2. string b = a; 形参传递; 都是调用copy constructor
(出现新对象,则调用的是~ ; 区别赋值运算符的重载)
3. 四种默认成员函数
*/
class string{
public:
	string();		
	string(const char* pstr);
	string(const string & rhs);
	string & operator=(const string & rhs);
	~string();
	void print();
private:
	char *_pstr;
};

string::string()
:_pstr(new char [1])
{
	//*_pstr='\0';
	cout<< "string()"<<endl;
}

string::string(const char* pstr)             //带参数的构造函数初始化
:_pstr(new char [strlen(pstr)+1])
{
	cout<< "string(const char* pstr)"<<endl;
	strcpy(_pstr,pstr);
}

string::string(const string & rhs)       //copy constructor,拷贝构造函数
:_pstr(new char [strlen(rhs._pstr)+1])
{
	cout<< "string(const string & rhs)"<<endl;
	strcpy(_pstr,rhs._pstr);                
}

#if 0
string & string::operator=(const string & rhs)
{
	cout<< "string & operator=(const string & rhs)"<<endl;
	_pstr=new char [strlen(rhs._pstr)+1];    //初始化表达式只能用于构造函数初始化成员变量
	strcpy(_pstr,rhs._pstr);                  //strcpyh会补加'\0'
}
#endif

string & string::operator=(const string & rhs)	//assignment,赋值函数(前提: 左值对象已经存在)
{
	if(this != &rhs) //1. 考虑自复制
	{
		delete [] _pstr;//2. 回收左操作数的空间,方便重新定义空间大小
		_pstr = new char[strlen(rhs._pstr) + 1]();//3. 再去进行深拷贝
		strcpy(_pstr, rhs._pstr);
	}
	return *this;
}


string::~string()
{
	delete  _pstr;
	_pstr=NULL;                            //避免出现野指针
	cout<<"~string() ok"<<endl;
}

void string::print(){
	cout<<"str = "<< _pstr <<endl;
}

int main(int argc,char** argv)
{
	string str1;
	str1.print();                        //无参数的构造函数
	
	string str2 = "Hello";    			 //string(const char* pstr)
	string str3("world");                //带参数的构造函数,string(const char* pstr)
	
	str2.print();		
	str3.print();	
	
	string str4 = str3;    //拷贝构造函数,string(const string & rhs);
	str4.print();
	
	str4 = str2;     //赋值运算符重载(前提: 左值对象str4已经存在)
	str4.print();
	
	return 0;
}