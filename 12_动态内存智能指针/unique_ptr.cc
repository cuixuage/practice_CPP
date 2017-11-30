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

unique_ptr<int> getValue()        //ʵ�ʵ���ʱ  1.������ֵ��ʱ����  ��Ϊupi������ֻ�Ǳ�����֮��   2.�ƶ����� ���Ա�unique_ptrʹ��
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

	//unique_ptr<Point> pt2 = pt;						//����ִ�и��Ʋ���,unique_ptr�Ƕ���������ָ��

														//��������ֵһ����Ҫ�����ٵ�unique_ptr  ����:���غ����ڲ��ֲ�����unique_ptr
	unique_ptr<int> upi2 = getValue();
	cout << "*upi2 = " << *upi2 << endl;


	return 0;
}
