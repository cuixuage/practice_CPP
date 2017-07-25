#include <iostream>
#include <stdio.h>
using std::cout;
using std::endl;
//主要作用:用来替换全局变量
//构造函数 析构函数都设置为private
//单实例最终会自动释放销毁

class singleton{
private:
	singleton(){};
	static singleton* _pInstance;
public:
	static singleton* getInstance(){
		if(_pInstance==NULL)
			_pInstance = new singleton;     
		return _pInstance;
	}
private:
	class Deleter
	{
	public:
		~Deleter()
		{
			if (singleton::_pInstance != NULL)
			{
				delete singleton::_pInstance;
				cout<< "~Deleter() ok"<<endl;
			}
		}
	};
	 // 定义一个静态成员，在程序结束时，系统会调用它的析构函数
	static Deleter _deleter;
};

singleton* singleton::_pInstance=NULL;     
singleton::Deleter  singleton::_deleter;             //静态成员类外初始化

int main(void)
{
	singleton * p1 = singleton::getInstance();    //使用静态成员函数
	singleton * p2 = singleton::getInstance();
	singleton * p3 = singleton::getInstance();

	printf("p1 = %p\n", p1);
	printf("p2 = %p\n", p2);
	printf("p3 = %p\n", p3);

	//delete p1;     //希望能够主动释放单例

	return 0;
}

