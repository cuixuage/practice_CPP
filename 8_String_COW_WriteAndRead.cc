
/*
	String 类Copy_On_Write 技术实现： 申请堆空间时而外申请sizeof(cahr)大小空间用于保存引用计数值
	
	Proxy 模式区别operator[]运算符的write(引用计数自减) , read情况  ————Effective C++
*/

#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class String{
public:
    class CharProxy;         //代理类 可以设置为友元

	String();
	~String();
	String(const char* pstr);

	String(const String &rhs);            //2种复制语义
	String & operator = (const String & rhs);

	CharProxy operator[] (size_t idx);    //重载[]
	friend std::ostream & operator<< (std::ostream &os ,const String &rhs);

	const char* c_str() const{
		return _pstr;
	}
	size_t size() const{
		return strlen(_pstr);
	}
	size_t refcount() const{         //获取引用计数值
		return _pstr[size()+1];
	}

private:
	void initRefcount(){             //引用计数的相关函数
		_pstr[(size()+1)] = 1;
	}
	void increaseRefcount(){
		++ _pstr[size()+1];
	}
	void decreaseRefcount(){
		-- _pstr[size()+1];
	}
	char * _pstr;
};

String::String()
:_pstr(new char [2]){
	//cout << "string()" << endl;
	initRefcount();
}

String::String(const char * pstr)
:_pstr(new char[strlen(pstr) + 2]){
	//cout << "String(const char *)" << endl;
	strcpy(_pstr,pstr);
	initRefcount();               //strcopy,初始化refcount=1
}

String::String(const String & rhs)
:_pstr(rhs._pstr){      //复制语义->浅拷贝->rhs指针赋值
	increaseRefcount();
}

String & String::operator = (const String &rhs){
	if(this != &rhs){
		decreaseRefcount();
		if(refcount() == 0){    //只有当this->refcount变为0时，才去回收左操作数的空间
			delete [] _pstr;
			cout<< "delete left _pstr" << endl;
		}
		_pstr = rhs._pstr;   //复制语义->浅拷贝->rhs指针赋值
		increaseRefcount();
	}
	return *this;       //注意返回值
}

String::~String(){
	decreaseRefcount();
	if(refcount()==0){
		delete [] _pstr;
		cout<< "~String" << endl;
	}
}

std::ostream & operator<< (std::ostream & os,const String &rhs){
	os << rhs._pstr;
	return os;
}



//*************************************CharProxy定义
class String::CharProxy{
public:
	CharProxy(String &, int );
	CharProxy & operator=(const char);
	friend std::ostream& operator<<(std::ostream &os, const CharProxy &rhs)
    {
        return os << rhs._mystr.c_str()[rhs._idx];    //避免 _mystr[idx]递归;
    }
private:
	String & _mystr;     //********传递一个引用!!!! 代理类不需要析构函数
	size_t _idx;
};

String::CharProxy::CharProxy(String & mystr, int idx)
:_mystr(mystr)
,_idx(idx){
    cout<<"String::CharProxy::CharProxy(String & mystr, int idx)() ok"<<endl;
}

String::CharProxy & String::CharProxy::operator=(const char c){
	if(_idx < _mystr.size()){
		if(_mystr.refcount()>1){          //待更新的str多个引用时
			_mystr.decreaseRefcount();
			char * ptmp = new char[_mystr.size()+2];
			strcpy(ptmp,_mystr._pstr);
			ptmp[_idx]=c;       		//写更新
			_mystr._pstr=ptmp;          //浅拷贝,同一块堆区
			_mystr.initRefcount();
		}
		return (*this);
	}
	else{
		String str;
		static CharProxy nullchar(str,0);
		cout<< "Proxy 越界" << endl;
		return nullchar;
	}
}

//保证CharProxy定义complete  string operator需要在最后
String::CharProxy String::operator[] (size_t idx){

     return CharProxy(*this , idx);
}

int main(int argc,char** argv){
	//*****************************************************测试复制语义
	String str1;
	String str2("hello,world");
	String str3(str2);
	cout << "str1 = " << str2 << endl;
	cout << "str2 = " << str2 << endl;
	cout << "str3 = " << str3 << endl;
	cout << "str1's refcount = " << str1.refcount() << endl;
	cout << "str2's refcount = " << str2.refcount() << endl;
	cout << "str3's refcount = " << str3.refcount() << endl;
	printf("&str1 = %p\n", str3.c_str());
	printf("&str2 = %p\n", str2.c_str());
	printf("&str3 = %p\n", str3.c_str());
	cout<<"----------------------------------"<<endl;
	str1 = str2;                       //str2 str3指向的字符串 引用计数+1
	cout << "str1 = " << str2 << endl;
	cout << "str2 = " << str2 << endl;
	cout << "str3 = " << str3 << endl;
	cout << "str1's refcount = " << str2.refcount() << endl;
	cout << "str2's refcount = " << str2.refcount() << endl;
	cout << "str3's refcount = " << str3.refcount() << endl;
	printf("&str1 = %p\n", str3.c_str());
	printf("&str2 = %p\n", str2.c_str());
	printf("&str3 = %p\n", str3.c_str());
	cout<<"----------------------------------"<<endl;
	String str4 = "wangdao";
	String str5(str4);         //此时str4引用计数=2
	str4=str2;                  //此时str2 的引用计数=4
	cout << "str2 = " << str2 << endl;
	cout << "str4 = " << str4 << endl;
	cout << "str5 = " << str5 << endl;
	cout << "str2's refcount = " << str2.refcount() << endl;
	cout << "str4's refcount = " << str4.refcount() << endl;
	cout << "str5's refcount = " << str5.refcount() << endl;
	printf("&str2 = %p\n", str2.c_str());
	printf("&str4 = %p\n", str4.c_str());
	printf("&str5 = %p\n", str5.c_str());
	//*************************************************测试operator [] 写操作
	cout<<"----------------------------------"<<endl;
	str1[0] = 'X';
	cout << "str1 = " << str1 << endl;
	cout << "str2 = " << str2 << endl;
	cout << "str3 = " << str3 << endl;
	cout << "str4 = " << str4 << endl;
	cout << "str1's refcount = " << str1.refcount() << endl;
	cout << "str2's refcount = " << str2.refcount() << endl;
	cout << "str3's refcount = " << str3.refcount() << endl;
	cout << "str4's refcount = " << str4.refcount() << endl;
	printf("&str1 = %p\n", str1.c_str());
	printf("&str2 = %p\n", str2.c_str());
	printf("&str3 = %p\n", str3.c_str());
	printf("&str4 = %p\n", str4.c_str());
	//*************************************************测试operator [] 读操作
	cout<<"----------------------------------"<<endl;
	cout<<"read str2[0]"<<str2[0]<<endl;       //read str[2] 不会发生COW情况 refcout 不改变
	cout << "str1 = " << str1 << endl;
	cout << "str2 = " << str2 << endl;
	cout << "str3 = " << str3 << endl;
	cout << "str4 = " << str4 << endl;
	cout << "str1's refcount = " << str1.refcount() << endl;
	cout << "str2's refcount = " << str2.refcount() << endl;
	cout << "str3's refcount = " << str3.refcount() << endl;
	cout << "str4's refcount = " << str4.refcount() << endl;
	printf("&str1 = %p\n", str1.c_str());
	printf("&str2 = %p\n", str2.c_str());
	printf("&str3 = %p\n", str3.c_str());
	printf("&str4 = %p\n", str4.c_str());

	return 0;

}

/*
	1.思考 private static 来保存引用计数值的错误设计
	2.String 重载[]但是无法进行左值、右值判断。=》只返回代理类对象，将左值右值判断放入代理类内部,再次重载代理类的 operator<<（右值情况）与 operator=（左值情况）
*/
