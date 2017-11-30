#include <iostream>
#include <memory>
#include <vector>
using std::cout;
using std::endl;
using std::shared_ptr;
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
		cout<<this->_ix<<"~ ";
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

int main(void)
//********************************************shared_ptr  use_count引用计数
{
	//shared_ptr<int> upi(new int(66));								//形如 shared_ptr<T> upi(new T())
	auto upi = std::make_shared<int>(66);								// make_shared<template>()  //第二种初始化方式
	cout << "*upi = " << *upi << endl;

	shared_ptr<Point> pt(new Point(1, 2));
	cout << "*pt =" << *pt << endl;
	cout << "pt's use_count = " << pt.use_count() << endl;

	shared_ptr<Point> pt3(new Point(3, 4));
	cout << "*pt3 = " << *pt3 << endl;

	shared_ptr<Point> pt2 = pt;
	cout << "pt's use_count = " << pt.use_count() << endl;
	cout << "pt2's use_count = " << pt2.use_count() << endl;          //pt2 pt 引用计数相同==2
	
	pt3 = pt;                                                          //过程:先将原来pt3析构释放掉，在将pt引用计数+1
																		//shared_ptr赋予另一个shared_ptr时 递增右侧引用计数 递减左侧引用计数
	cout << "pt's use_count = " << pt.use_count() << endl;
	cout << "pt2's use_count = " << pt2.use_count() << endl;
	cout << "pt3's use_count = " << pt3.use_count() << endl;          //pt3 pt2 pt 引用计数相同==3
	cout << endl;

	shared_ptr<Point> pt4(new Point(1, 2));                      //pt4对象虽然和pt对象内容值相同，但是他们不等价，是两个不同对象  
	cout << "pt4's use_count = " << pt4.use_count() << endl;     //pt4引用计数==1

	return 0;
}
