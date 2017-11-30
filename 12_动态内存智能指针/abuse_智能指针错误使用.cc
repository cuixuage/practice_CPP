#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;
using std::unique_ptr;

class Point
: public std::enable_shared_from_this<Point>  //在类内部获取本对象的shared_ptr的方式
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{
		cout << "Point(int,int)"
			 << endl;
	}


	~Point()
	{
		cout << "~Point()" << endl;
	}

#if 0
	//test2错误使用??    感觉没有问题？？
	Point * addPoint(Point * pt)
	{
		_ix += pt->_ix;
		_iy += pt->_iy;
		cout<<"what"<<endl;
		return this;
	}
#endif

#if 1
	shared_ptr<Point> addPoint(Point * pt)				//类外 对象调用public函数可以访问自身私有变量
	{
		_ix += pt->_ix;
		_iy += pt->_iy;
		return shared_from_this();				//版本2  析构2次
		//return std::shared_ptr<Point>(this);     	//版本1  析构3次
	}
#endif

	friend std::ostream & operator<<(std::ostream & os, const Point & rhs);
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

int test0(void)
{//误用1: 同时将一个原生裸指针交给不同的智能指针进行托管				//error:同一对象被多次free
	Point * p1 = new Point(1, 2);
	shared_ptr<Point> sp1(p1);
	shared_ptr<Point> sp2(p1);
	unique_ptr<Point> up1(p1);

	return 0;
}

int test1()
{//误用2									    //不使用get初始化 或者reset另外一个智能指针
	Point * p1 = new Point(1, 2);
	shared_ptr<Point> sp1(p1);
	shared_ptr<Point> sp2(new Point(3, 4));

	sp2.reset(sp1.get());						//get()返回指向(1,2)的指针 ;reset()释放对象 ;reset(q)使得sp2指向q指针所指向的对象
												//一旦sp1被释放 那么指针q变得无效
	cout << "*sp2 = " << *sp2 << endl;
	return 0;
}

int test2()
{//误用3: 函数的返回值是一个原生裸指针 
	shared_ptr<Point> sp1(new Point(1, 2));
	shared_ptr<Point> sp2(new Point(3, 4));

	shared_ptr<Point> sp3(sp1->addPoint(sp2.get()));				//sp3 sp1共享数据  (4,6)

	cout << *sp1 << endl;
	cout << *sp3 << endl;
	return 0;
}


int main(void)
{
	//test0();
	//test1();
	test2();
	return 0;
}
