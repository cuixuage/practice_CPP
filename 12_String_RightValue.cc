
//添加  移动语义的构造函数、赋值函数    右值引用&&

#include <iostream>
#include <string.h>
#include <stdio.h>
using std::cout;
using std::cin;
using std::endl;

class String {
public:
	String();
	String(const char *);
	String(const String&);
	~String();
	String &operator=(const String &);
	String &operator=(const char *);
	
	//右值引用 
    String(String &&rhs);             //移动语义的构造函数
    String & operator=(String &&rhs); //移动语义的operator=赋值语义
   
   
	String &operator+=(const String &);
	String &operator+=(const char *);

	char &operator[](std::size_t index);
	const char &operator[](std::size_t index) const;          //const对象只能调用const成员函数;普通对象均能调用

	std::size_t size() const;
	const char* c_str() const;

	friend bool operator==(const String &, const String &);
	friend bool operator!=(const String &, const String &);

	friend bool operator<(const String &, const String &);
	friend bool operator>(const String &, const String &);
	friend bool operator<=(const String &, const String &);
	friend bool operator>=(const String &, const String &);

	friend std::ostream &operator<<(std::ostream &, const String &);
	friend std::istream &operator>>(std::istream &, String &);

private:
	char * _pstr;
};

String operator+(const String &, const String &);
String operator+(const String &, const char *);
String operator+(const char *, const String &);

String::String()
:_pstr(new char[1])
{
}

String::String(const char* pstr)
:_pstr(new char[strlen(pstr)+1])
{
	cout<< "String(const char *)" <<endl;
	strcpy(_pstr,pstr);
}

String::String(const String & rhs)
:_pstr(new char[strlen(rhs._pstr)+1])
{
	cout<< "String (const Sting &)"<<endl;
	strcpy(_pstr,rhs._pstr);
}
//*********************************************临时对象右值引用&&  
String::String(String && rhs)
:_pstr(rhs._pstr)
{
	cout << "Sting(Sting && rhs)" <<endl;
	rhs._pstr = NULL;            //右值rhs自动释放时
}

String & String::operator=(String && rhs){
	cout << "operator = (Sting && rhs)" <<endl;
	if(this != &rhs){
		delete [] _pstr;
		this->_pstr = rhs._pstr;
		rhs._pstr =  NULL;
	}
	return *this;
}
//***********************************************
String::~String(){
	delete [] _pstr;
}

String & String::operator=(const String &rhs){
	if(this != &rhs){        //避免自复制问题 左右均为指针
		delete [] _pstr;
		_pstr=new char [strlen(rhs._pstr)+1];
		strcpy(_pstr,rhs._pstr);
	}
	return *this;
}
	
String & String::operator=(const char * pstr){
	if(!strcmp(this->_pstr,pstr)){         //判断字符串内容是否相同;pstr在文字常量区,_pstr在栈区,首地址肯定不相同
		cout << "operator = (const char *)" <<endl;
		delete [] _pstr;
		_pstr=new char [strlen(pstr)+1];
		strcpy(_pstr,pstr);
	}
	return *this;
}

String & String::operator+=(const String& rhs){
	int need_length=strlen(this->_pstr)+strlen(rhs._pstr)+1;
	char *temp=new char [strlen(_pstr)+1];
	strcpy(temp,_pstr);
	delete [] _pstr;
	_pstr = new char [need_length];
	strcpy(_pstr,temp);
	delete [] temp;
	strcat(_pstr,rhs._pstr);
	return *this;
}
	
String & String::operator+=(const char* pstr){
	int need_length=strlen(this->_pstr)+strlen(pstr)+1;
	char *temp=new char [strlen(_pstr)+1];
	strcpy(temp,_pstr);
	delete [] _pstr;
	_pstr = new char [need_length];
	strcpy(_pstr,temp);
	delete [] temp;
	strcat(_pstr,pstr);
	return *this;
}
	
char & String::operator[](std::size_t index){
	static char nullchar = '\0';
	if(index>=0 && index<strlen(_pstr)){
		return _pstr[index];
	}
	return nullchar;
	//return '\0';     //引用不要返回局部变量
}

const char & String::operator[](std::size_t index) const{          //const对象只能调用const成员函数;普通对象均能调用
	static char nullchar = '\0';
	if(index>=0 && index<strlen(_pstr)){
		return _pstr[index];
	}
	return nullchar;
}
	
std::size_t String::size() const{
	if(*(this->_pstr)=='\0') return 0;
	return strlen(this->_pstr);
}

const char* String::c_str() const{
	return _pstr;                    //返回char* 
}

//A类的友元函数 能直接访问A类的private成员变量

bool operator==(const String &left, const String &right){
	return !strcmp(left._pstr,right._pstr);
}

bool operator!=(const String &left, const String &right){
	return strcmp(left._pstr,right._pstr);
}

bool operator<(const String &left, const String &right){
	return strcmp(left._pstr,right._pstr)<0?true:false;
}

bool operator>(const String &left, const String &right){
	return strcmp(left._pstr,right._pstr)>0?true:false;
}

bool operator<=(const String &left, const String &right){
	return strcmp(left._pstr,right._pstr)<=0?true:false;
}

bool operator>=(const String &left, const String &right){
	return strcmp(left._pstr,right._pstr)>=0?true:false;
}

std::ostream &operator<<(std::ostream &os, const String &rhs){       //对于String类 输出流重载
	os << rhs._pstr;
	return os;
}
	
std::istream &operator>>(std::istream &is, String &rhs){
	delete [] rhs._pstr;
	rhs._pstr=new char[256]{0};
	is >> rhs._pstr;          
	return is;
}
	
	
	String operator+(const String &, const String &);
	String operator+(const String &, const char *);
	String operator+(const char *, const String &);
String operator+(const String &left, const String &right){   //String += String
	String temp1(left);
	String temp2(right);    //初始化两个实例
	temp1 +=temp2;
	return temp1;           //返回String 对象
}
String operator+(const String &left, const char *right){    //String += char*
	String temp1(left);
	//String temp2(right);    
	temp1 +=right;
	return temp1;           //返回String 对象
}
String operator+(const char *left, const String &right){     //要求 left在前
	String temp1(left);
	String temp2(right);    
	temp1 +=temp2;
	return temp1;           //返回String 对象
}	
	
int main(int argc,char ** argv){

	//编译器只对右值引用才能调用转移构造函数和转移赋值函数
	//********************** 右值引用&&测试
	String str15 ("hello");             //构造函数(const char *)
	String str16 ("world");
	String str17(std::move(str15));     //右值构造函数
	cout<<str17<<endl;
	cout<<"---------------------"<<endl;
	str15 = std::move(str16);            //右值赋值函数
	cout<<str15<<endl;
	
	return 0;
}
