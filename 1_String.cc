#include <iostream>
#include <string.h>    //包含对于字符串的处理函数
using std::cout;
using std::endl;

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

string::string(const string & rhs)       //复制构造函数  对象的复制
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

string & string::operator=(const string & rhs)
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
	
	string str2 = "Hello";    
	string str3("world");                //带参数的构造函数
	
	str2.print();		
	str3.print();	
	
	string str4 = str3;    // 深拷贝复制构造函数     类名(const 类名 & rhs)
	str4.print();
	
	str4 = str2;     //运算符的重载        类名 & operator=(const 类名 & rhs)
	str4.print();
	
	return 0;
}