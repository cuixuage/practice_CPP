
//HeapSort 模版类   使用Compare函数对象

#include <iostream>
#include <vector>
#include <math.h>
using std::cout;
using std::endl;
using std::vector;

template <typename T, typename Compare = std::less<T>> //函数对象compare, 默认为std::less
class HeapSort
{
public:
	HeapSort(vector<T> & array)     //构造函数  实参引用
	: _array(array)
	{}
	void sort();                    //排序接口
	void print() const;
private:
	vector<T> _array;               //底层保存数据
	void heapAdjust(int parent, int size);
	void makeHeap();
};

template <typename T, typename Compare>
void HeapSort<T, Compare>::heapAdjust(int parent, int size)
{
	Compare comp;                                   //函数对象compare
	T temp = _array[parent];                        //parent由编号零起
	int child = 2 * parent + 1;
	while(child < size)
	{
		if(child + 1 < size &&
		   comp(_array[child], _array[child + 1]))
			++child;                                     //如果存在两个子节点 找到最大的子节点

		//if(temp < _array[child]) 
		if(comp(temp, _array[child]))         //父节点小于最大的子节点-》调整为大顶
		{
			_array[parent] = _array[child];
			parent = child;
			child = 2 * parent + 1;
		}
		else
			break;
	}
	_array[parent] = temp;      //parent结点调整完毕
}

template <typename T, typename Compare>
void HeapSort<T, Compare>::makeHeap()
{
	for(int idx = _array.size() / 2 - 1; idx >= 0; --idx)     //first非叶子结点开始调整
	{
		heapAdjust(idx, _array.size());
	}
}

template <typename T, typename Compare>
void HeapSort<T, Compare>::sort()
{
	makeHeap();	                      //得到大顶堆
	for(int idx = _array.size() - 1; idx > 0; --idx)   //排序
	{
		std::swap(_array[0], _array[idx]);
		heapAdjust(0, idx);
	}
}

template <typename T, typename Compare>
void HeapSort<T, Compare>::print() const
{
	typename vector<T>::const_reverse_iterator crit = _array.rbegin();
	for(; crit != _array.rend(); ++crit)
	{
		cout << *crit << "  ";
	}
	cout << endl;
}
//***********************************************************Point类型
class Point
{
public:
	/*     //提供无参(参数有默认初始值)的构造函数,以免template初始化error
	Point()
	:_ix(0)
	,_iy(0){}
	*/
	Point(int ix=0, int iy=0)
	: _ix(ix)
	, _iy(iy)
	{}

	friend std::ostream & operator<<(std::ostream & os, const Point &rhs);
	friend bool operator<(const Point & lhs, const Point & rhs);
	friend bool operator>(const Point & lhs, const Point & rhs);

	float distance() const
	{
		return sqrt(_ix * _ix + _iy * _iy);
	}

private:
	int _ix;
	int _iy;
};
std::ostream & operator<<(std::ostream & os, const Point &rhs)
{
	os << "(" << rhs._ix
	   << "," << rhs._iy
	   << ")";
	return os;
}

bool operator<(const Point & lhs, const Point & rhs)
{
	return lhs.distance() < rhs.distance();
}

bool operator>(const Point & lhs, const Point & rhs)
{
	return lhs.distance() > rhs.distance();
}

struct Compare
{
	bool operator()(const Point & lhs, const Point & rhs)const
	{
		//cout << "Compare()" << endl;      //每比较一次都会打印一次输出
		return lhs.distance() < rhs.distance();
	}
};

//********************************************************* less "<"   大顶堆
void test0(void)
{
	vector<int> numbers{3, 2, 5, 8, 9, 7, 6, 4, 0, 1};

	HeapSort<int> hs(numbers);
	hs.sort();
	hs.print();
}

//*******************************************************geater ">"  小顶堆
void test1(void)
{
	vector<int> numbers{3, 2, 5, 8, 9, 7, 6, 4, 0, 1};

	HeapSort<int, std::greater<int> > hs(numbers);
	hs.sort();
	hs.print();

}

//*******************************************************自定义 Point类型排序
void test_Point(){
	//Point[] array={}  //错误:底层数据保存不能使用数组
    vector<Point> a= {Point(0,0),Point(1,1),Point(2,2),Point(-1,-1),Point(-2,2),Point(3,3),Point(5,5),Point(7,7),Point(4,4),Point(6,6),Point(0,1)};   
	
	//方式一: 自定义Compare类重载operator() ,再作为函数对象传入
	//方式二： 重载operator > 使用std::greater  =》 比较时寻找到Point对象operator > 已被重载
	//HeapSort<Point, Compare> hs(a);
	HeapSort<Point, std::greater<Point> > hs(a);
	hs.sort();
	hs.print();
}
int main(void)
{
	test0();
	test1();
	test_Point();
}
