
//实现Stinrg 类中 构造函数、运算符= += == != > < >= <=、输入输出流istream ostream的重载

#include <iostream>
//#include <String>    //不加入此头文件
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
	*_pstr='\0';
}

String::String(const char* pstr)
:_pstr(new char[strlen(pstr)+1])
{
	strcpy(_pstr,pstr);
}

String::String(const String & rhs)
:_pstr(new char[strlen(rhs._pstr)+1])
{
	strcpy(_pstr,rhs._pstr);
}

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
	os << rhs._pstr<<endl;
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
	//**********************构造函数测试
	String str1;
    String str2("hello,world");
	String str3(str2);
	cout<<str1;
	cout<<str2;
	cout<<str3;
	cout<< String("---------------------");
	
	//***********************  = 运算符测试
	const char *pstr="hello,world,cui";
	String str4=pstr;
	String str5=str4;
	cout<<str4;
	cout<<str5;
	cout<< String("---------------------");
	
	//********************** += 运算符测试
	String str6("hello,");
	str6 +=str6;
	cout<<str6;
	str6 += "cuixuange";
	cout<<str6;
	cout<< String("---------------------");

	//********************** [] 运算符测试
	String str7("Hello");
    const String str8("CUIXUANGE");
	cout<<str7[0]<<endl;             //单个字符输出不会调用 重载的string输出;  额外加上换行符
	cout<<str8[8]<<endl;
	cout<< String("---------------------");
	
	//********************** size c_str 函数测试
    cout << "size():"<<str8.size()<<endl;
	cout<<str8.c_str()<<endl;
	cout<< String("---------------------");
	
	//********************** == != > < >= <= 运算符测试
	String str9="hello";
	String str10="Hello";
	cout<<"NOTE: true is 1 ; false is 0"<<endl;
	cout<<"==? "<<(str9==str10)<<endl;
	cout<<"!=? "<<(str9!=str10)<<endl;
	cout<<"> ? "<<(str9> str10)<<endl;
	cout<<"< ? "<<(str9< str10)<<endl;
	cout<<">=? "<<(str9>=str10)<<endl;
	cout<<"<=? "<<(str9<=str10)<<endl;
	cout<< String("---------------------");
	
	//********************** << >>运算符测试 
	String str11;
	cout<<"input something...."<<endl;
	cin>>str11;
	cout<<"cin:"<<str11;
	cout<< String("---------------------");   //测试 << 流
	
	//********************** + 运算符测试 
	String str12;
	String str13("hello");
	String str14(",world");
	const char *pstr2=",world";
	str12 = str13 + str14;
	cout<<"string + string:       "<<str12;
	str12 =str13 + pstr2;
	cout<<"string + const char*: " << str12;
	str12 = pstr2 + str13 ;
	cout<<"const char* + string: " << str12;
 	
	return 0;
}
/*
1.友元函数
有三种类型 自由函数，其他类的成员函数, 友元类 。 被定义的友元内容 能够直接访问当前类的private 私有成员变量

2.运算符重载原则
操作数必须为用户自定义的类、枚举类；优先性、结合性是固定的；一般不重载 && || 等逻辑运算符

3.不能重载的运算符
成员访问符 .       成员指针访问运算符 .*            域运算符 ::
长度运算符 sizeof	         条件运算符号 ?:

4.运算符重载形式
自由函数重载operator  例如 + ，-。返回一个新的实例 
友元函数重载operator   能访问类私有成员
成员函数重载operator  例如 ++ += 。返回一个实例的引用,因为左值一般已经存在,避免返回新实例 浅拷贝出错、 也提高了效率

5.前置++ 后置++区别
前置++ 返回this的引用   ;   后置++ 返回this的复制对象
前置++ 在容器的迭代器中使用能提高使用效率
前置++和后置++参数和返回值类型不同
后置++有一个(int)类型参数，调用时编译器传递一个0作为该(int)的值

*/