
//模版类Heapsort  HeapSort<int>  HeapSort<自定义类> 进行堆排序测试

#include <math.h>
#include <iostream>
using std::cout;
using std::endl;

template <typename T >
class HeapSort{
public:
    HeapSort(T * arr, int size);   
	void shift(T  r[], int k, int m);	
    void heapAdjust(); 
private:
	T * & _arr;
	int _size;
};

template <typename T >
HeapSort<T>::HeapSort(T * arr, int size)
:_arr(arr)
,_size(size){
	for (int i = _size / 2; i > 0; i--)  //建堆
        shift(_arr, i, _size);
    for (int j = _size; j > 0; j--)
    {
        T temp = _arr[j];
        _arr[j] = _arr[1];
        _arr[1] = temp;
        shift(_arr, 1, j - 1);  //当前最大值结点移到数组最后,仅调整 前j-1个元素
    }
}

template <typename T >
void HeapSort<T>::shift(T r[], int k, int m)
{//要筛选的节点编号为k，堆中最后一个节点为m
    int i, j;
	T	temp;
    i = k;
    j = 2*i;  //编号为k的节点的左孩子
    temp = r[i];//将筛选记录暂存(需要调整的位置)
    while(j<=m)//筛选还没进行到的叶子
    {
        if(j<m && r[j]<r[j+1])//j<m说明i节点还有一个右孩子，为二度节点
        {
            j++;//i有两个孩子，取大孩子
        }

        //一个孩子或者左孩子比右孩子大
        if(r[i] > r[j])
        {
            break;//孩子比父亲小
        }

        else//孩子比父亲大
        {
            r[i] = r[j];//将较大的节点移到根上。
            i = j;
            j = 2*i;
            //将i指向交换的位置，为进一步移动做准备。
        }
        r[i] = temp;//将筛选记录移到正确位置
    }
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


void test_int(){
	int size=10;
    int a[] = {0,4,5,8,2,1,6,7,9,10,3};    //a[0]不参与排序
    cout << "大顶堆排序前的序列:" << endl;
    for (int i = 1; i <= size; i++)
    {
       cout << a[i] << "  ";
    }
    HeapSort<int>(a, size);
	cout<<endl;
    cout << "大顶堆排序后的序列:" << endl;
    for (int i = 1; i <= size; i++)
    {
        cout << a[i] << "  ";
    }
	cout<<endl;
}

void test_Point(){
	int size=10;
    Point a[] = {Point(0,0),Point(1,1),Point(2,2),Point(-1,-1),Point(-2,2),Point(3,3),Point(5,5),Point(7,7),Point(4,4),Point(6,6),Point(0,1)};    //a[0]不参与排序
    cout << "大顶堆排序前的序列:" << endl;
    for (int i = 1; i <= size; i++)
    {
       cout << a[i] << "  ";
    } 
     HeapSort<Point>(a, size);        
	cout<<endl;
    cout << "大顶堆排序后的序列:" << endl;
    for (int i = 1; i <= size; i++)
    {
        cout << a[i] << "  ";
    }
	cout<<endl;
}

int main(){
	//test_int();
	
	test_Point();
    return 0;
}