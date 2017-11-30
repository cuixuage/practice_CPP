#include <iostream>
#include <memory>
#include <vector>
using std::cout;
using std::endl;
using std::unique_ptr;
using std::vector;

class Point
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{
		cout << "Point(int,int)"
			 << endl;
	}

	friend std::ostream & operator<<(std::ostream & os, const Point & rhs);

	~Point()
	{
		cout << "~Point()" << endl;
	}

private:
	int _ix;
	int _iy;
};

std::ostream & operator<<(std::ostream & os, const Point & rhs)
{
	os << "(" << rhs._ix
	   << "," << rhs._iy
	   << ")";
	return os;
}

unique_ptr<int> getValue()        //实际调用时  1.返回右值临时对象  因为upi作用域只是本函数之内   2.移动语义 可以被unique_ptr使用
{
	unique_ptr<int> upi(new int(88));
	return upi;
}


int main(void)
{
	unique_ptr<int> upi(new int(66));
	cout << "*upi = " << *upi << endl;
	unique_ptr<Point> pt(new Point(1, 2));
	cout << "*pt =" << *pt << endl;

	//unique_ptr<Point> pt2 = pt;						//不能执行复制操作,unique_ptr是独享型智能指针

														//允许拷贝或赋值一个将要被销毁的unique_ptr  例如:返回函数内部局部变量unique_ptr
	unique_ptr<int> upi2 = getValue();
	cout << "*upi2 = " << *upi2 << endl;


	return 0;
}
