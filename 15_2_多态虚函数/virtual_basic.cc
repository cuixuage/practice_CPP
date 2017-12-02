#include <iostream>
using std::cout;
using std::endl;

//Ŀ��:��̬    ����:��ͬ���Ͷ������ͬһ����(�˺����ڲ�ʹ���ض�����麯��)���Ӷ�����ֵ��ͬ
//virtual�������ȡ����ָ����ָ��������͡��������ݲ�ͬ�����������õ�display������ͬ

class Base
{
public:
	virtual 
	int func(int x)
	{
		cout << "Base::func(int) x = " << x << endl; 
		return 0;
	}
private:
	double _dx;
};

class Sub
: public Base
{
public:
#if 1
	//virtual
	int func(int x)							//����������virtual ���ǻ�����ͬ���麯��
	{
		cout << "Sub::func(int) x = " << x << endl;
		return x;
	}
#endif

	virtual 
	int func()  //����Sub��һ�����麯��  	//�����������Ͳ�ͬ�ڻ���
	{
		return 0;
	}
private:
	double _dy;
};

/*
��̬��̬���麯�����ƣ��������������
1. ����Ҫ����һ���麯��
2. ������Ҫ���Ǹ��麯��
3. �����ָ���������ָ�����������
4. ��ָ������õ����麯��
*/

void display(Base * pbase)
{
	pbase->func(10);
}

void print(Base & base)
{
	base.func(1);
}

/*
1.����ָ���ܹ�ָ�����������   ֻ��ָ�����Ͳ�ͬ����
2.���������ָ�����������
*/
int test0(void)
{
	Base base;
	Sub sub;
	display(&base);
	display(&sub);				//���������� display
	return 0;
}

int test1()
{
	Base base;
	Sub sub;
	print(base);
	print(sub);					//���������� display
	return 0;
}

int main(void)
{
	cout << "sizeof(Base) = " << sizeof(Base) << endl;           //16bytes = vfptrָ��8bytes(64λ) + double 8bytes
	cout << "sizeof(Sub) = " << sizeof(Sub) << endl;             //24bytes = 16(����) + double 8bytes

	test0();
	cout<<endl;
	test1();
	
	return 0;
}
