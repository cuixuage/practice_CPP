#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
/*
	һ����˵����������ж������麯����������������ҲӦ������Ϊ����������������������������Ķ�̬�ڴ棬��Ҫ������ͷŵ�ʱ��
	�����ڴ�й©
	
	����:����new֮��; delete pbase;			//���ݶ�������ִ�ж�Ӧ���������� ���Ǹ���ָ��phase������
*/
class Base
{
public:
	Base(const char * pbase)
	: _pbase(new char[strlen(pbase) + 1]())
	{
		cout << "Base(const char*)" << endl;
		strcpy(_pbase, pbase);
	}

	virtual
	~Base()
	{
		cout << "~Base()" << endl;
		delete [] _pbase;
	}

	virtual
	void display() const
	{
		cout << _pbase;
	}
private:
	char * _pbase;
};

class Child : public Base
{
public:
	Child(const char * pbase, const char * pchild)
	: Base(pbase)
	, _pchild(new char[strlen(pchild) + 1]())
	{
		cout << "Child()" << endl;
		strcpy(_pchild, pchild);
	}

	//һ�����������������Ϊ�麯��֮��������������������Զ���Ϊ�麯��
	//��ʹû�и���virtual�ؼ���
	~Child()
	{
		cout << "~Child()" << endl;
		delete [] _pchild;
	}

	virtual
	void display()const
	{
		Base::display();
		cout << _pchild << endl;
	}

private:
	char * _pchild;
};


int main(void)
{
	Base * pbase = new Child("hello,", "world");     	//����ָ��ָ�� �������

	pbase->display();

	delete pbase;			//������Ҫ���õ������������������
	
	//��������������������virtual ��ô����ֻ����û������������
	
	//ָ������ΪBase ,���ǹ��캯��Ϊvirtual ,���Ի����ִ��ʵ��ָ��������������
}



/*
output:
Base(const char*)				//��ִ�л��๹�캯��(����������virtual)
Child()
hello,world
~Child()						//ִ����������  ��Ȼ��ʱdelete��Base���͵�ָ�� child��������
~Base()
*/

