#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;


class X
{
public:
	X(){	cout << "X()" << endl;	} 
	~X(){	cout << "~X()" << endl;	}

	void func()
	{	cout << "X::func()" << endl;	}
};

int main(void)
{
	shared_ptr<X> sp(new X);																
	cout << "sp 's use_count = " << sp.use_count() << endl;		//use_count返回share_ptr引用计数

	weak_ptr<X> wp;												//使用shared_ptr初始化 weak_ptr<X> wp(sp);
	wp = sp;													//弱共享不会改变share_ptr引用计数
	
	cout << "sp 's use_count = " << sp.use_count() << endl;

	shared_ptr<X> sp2 = wp.lock();								//wp.lock函数检测weak_ptr指向的对象是否存在,
																//存在,则返回指向共享对象的share_ptr
	if(sp2)
	{
		cout << "提升成功"<< endl;
		sp2->func();
	}
	else
	{
		cout << "提升失败，该对象已被销毁!" << endl;
	}
	
	shared_ptr<X> sp3 = wp.lock();								//lock不影响weak_ptr本身的存在  仍然成功
	if(sp3)
	{
		cout << "提升成功"<< endl;
		sp3->func();
	}
	else
	{
		cout << "提升失败，该对象已被销毁!" << endl;
	}

	return 0;
}
