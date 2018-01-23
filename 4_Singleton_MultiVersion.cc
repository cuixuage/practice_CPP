//********************版本1
/*
	pthread_once 保证多线程环境下懒汉单例模式安全 
	atexit        注册程序结束时的销毁函数,自动销毁单实例
	
	int pthread_once(pthread_once_t * once_control , void(* init_routine)(void)); 
	1.其中pthread_once_t once_control = PTHREAD_ONCE_INIT;
	2.init_routine是函数指针 
	3.使用相同的once_control的pthread_once() 的后续调用不能调用init_routine
	4.成功返回0  失败返回 error number

	int atexit(void (*function)(void))
	1.成功返回0  失败返回 error number
	2.可以重复调用
*/
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
using std::cout;
using std::endl;
class Singleton
{
public:
	static Singleton * getInstance()
	{
		pthread_once(&_once_control, init_routine);     //静态成员函数只能使用静态成员,故_once_control、init_routine函数指针为static
		return _pInstance;
	}

	static void init_routine()     //多线程环境仍然能保证仅执行一次 ->  创建单实例对象+注册atexit函数
	{
		_pInstance = new Singleton;	
		atexit(destroy);          //注册退出后执行的函数destory, 实现单实例的自动释放
	}

	static void destroy()
	{
		if(_pInstance)
			delete _pInstance;
	}
private:
	Singleton(){	cout << "Singleton()" << endl;	}  //首先保证:构造函数private; 避免类外直接构造
	~Singleton(){	cout << "~Singleton()" << endl;	}
private:
	static Singleton * _pInstance;
	static pthread_once_t _once_control;
};

Singleton * Singleton::_pInstance = NULL;
pthread_once_t Singleton::_once_control = PTHREAD_ONCE_INIT;

int main(void)
{
	//*****************单例模式测试
	Singleton *s1=Singleton::getInstance();
	Singleton *s2=Singleton::getInstance();
	Singleton *s3=Singleton::getInstance();
	cout<<"addr: "<<s1<<endl;
	cout<<"addr: "<<s2<<endl;
	cout<<"addr: "<<s3<<endl;
	
	return 0;
}

//********************************版本2
/*
	atexit + 饱汉式
*/	
#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;
class Singleton
{
public:
	static Singleton * getInstance()
	{
		if(NULL == _pInstance)
		{
			_pInstance = new Singleton;
			atexit(destroy);
		}
		return _pInstance;
	}

	static void destroy()
	{
		if(_pInstance)
			delete _pInstance;
	}
private:
	Singleton(){	cout << "Singleton()" << endl;	}
	~Singleton(){	cout << "~Singleton()" << endl;	}
private:
	static Singleton * _pInstance;
};

Singleton * Singleton::_pInstance = getInstance();//饱汉式, 可以保证是线程安全的  //缺点：该对象会一直存在,即使在当前没有立即使用
int main(void)
{
	Singleton::getInstance();

	return 0;
}

//************************************************版本3
/*
	静态嵌套类对象实现单实例的自动销毁
*/	

#include <iostream>
using std::cout;
using std::endl;
// 静态的嵌套类对象(保存在全局区)  实现单实例的自动释放
class Singleton
{
private:
	class AutoRelease
	{
	public:
		AutoRelease()
		{
			cout << "AutoRelease()" << endl;
		}

		~AutoRelease()
		{
			cout << "~AutoRelease()" << endl;
			if(_pInstance)
				delete _pInstance;             //嵌套类内部 释放单实例
		}
	};
public:
	//懒汉模式在多线程环境下并不是线程安全的
	static Singleton * getInstance()
	{
		if(NULL == _pInstance)
			_pInstance = new Singleton;
		return _pInstance;
	}
private:
	Singleton(){	cout << "Singleton()" << endl;	}
	~Singleton(){	cout << "~Singleton()" << endl;	}
private:
	static Singleton * _pInstance;
	static AutoRelease _auto;
};

//懒汉式/饿汉式
//Singleton * Singleton::_pInstance = NULL;//懒加载
Singleton * Singleton::_pInstance = getInstance();//饱汉式, 可以保证是线程安全的 //缺点：该对象会一直存在,即使在当前没有立即使用

Singleton::AutoRelease Singleton::_auto;   //静态的嵌套类对象

int main(void)
{
	Singleton::getInstance();

	return 0;
}



/* 思考:
1.如何保证单例？ 首先构造函数private处理.。这样只能够在
2.为何使用static？ 因为最开始无法直接new对象，只能通过class::func访问静态成员函数 
*/
	