#include <iostream>
#include <memory>
using std::cout;
using std::endl;

template <typename T>
class Vector{
public:
	Vector();
	~Vector();
	void push_back(const T &);
	void pop_back();
	void clear();
	const T &operator[] (int idx) const;
	
	int size() const{						//元素个数
		return _firstFree - _elems;
	}
	int capacity() const{					//最大容量
		return _end - _elems;
	}

private:
	void reallocate();   //push_back时检测 size() == capacity()？

private:
	static std::allocator<T> _alloc;   //空间分配接口层的静态对象
	T * _elems;
	T * _firstFree;
	T * _end;
};

template <typename T>
Vector<T>::Vector()
:_elems(0)
,_firstFree(0)
,_end(0){
	cout << "Vector() ok" <<endl;
}

template <typename T>
Vector<T>::~Vector(){
	if(_elems){
		while(_elems != _firstFree)
			_alloc.destroy(--_firstFree);				//先自减; destroy(p) 删除指针p指向对象T
		_alloc.deallocate(_elems,capacity());			//deallocate(p,n)  释放p开始n个对象的内存(先对每一个元素进行destory)
	}
	cout<< "~Vector() ok"<<endl;
}

template <typename T>
void Vector<T>::push_back(const T & value){
	if( size() == capacity() )
		reallocate();
												//直接传递了一个T 对象
	_alloc.construct(_firstFree++ , value);     //元素的添加 实际调用定位表达式new((void*)Pointer)T(value)
}

template <typename T>
void Vector<T>::pop_back(){
	if(size()>0){
		_alloc.destroy(--_firstFree);			
	}
}

template <typename T>
const T & Vector<T>::operator[] (int idx) const {
	return _elems[idx];
}

/*
旧空间内容转移到新空间
方案1:
uninitialized_copy(b,e,b2);
allocator伴随函数 对于未初始化的b2内存 使用b,e两个iterator之间的元素拷贝填充

方案2:
T * newelems = _alloc.allocate(newcapacity);
for(size_t i=0; i!=this->size();++i){
	_alloc.construct(newelems++,std::move(*_elems++));

*/
template <typename T>
void Vector<T>::reallocate(){
	//计算新空间大小
	int oldcapacity = capacity();
	int newcapacity = (oldcapacity == 0 ? 1 : oldcapacity * 2);
	
	//1.分配新空间
	T * newelems = _alloc.allocate(newcapacity);
	if(_elems){
		//2.原始空间  uninitialized_copy( InputIt first, InputIt last, ForwardIt d_first );
		std::uninitialized_copy(_elems,_firstFree,newelems);
		//3.销毁原空间对象
		while(_elems != _firstFree)
			_alloc.destroy( --_firstFree);
		//4.销毁原空间
		_alloc.deallocate(_elems,oldcapacity);
	}
	//5.更新为新空间   在if语句外侧
	_elems = newelems;
	_firstFree = newelems + oldcapacity;
	_end = newelems + newcapacity;
	
}

template <typename T>
void Vector<T>::clear(){
	while(_elems != _firstFree)
		_alloc.destroy(--_firstFree);
	_alloc.deallocate(_elems,capacity());
	cout<< "clear ok"<<endl;
}


template <typename T>
std::allocator<T> Vector<T>:: _alloc;    //static 对象类外初始化

void display(const Vector<int> & vec)
{
	cout << "vec's size = " << vec.size() << endl;
	cout << "vec's capa = " << vec.capacity() << endl;
}

void print(const Vector<int> & vec)
{
	for(int idx = 0; idx < vec.size(); ++idx)
	{
		cout << vec[idx] << " ";
	}
}

int main(void)
{
	Vector<int> vec;
	//*******************************size() capacity()测试
	display(vec);
	vec.push_back(1);
	display(vec);
	vec.push_back(2);
	display(vec);
	vec.push_back(3);
	display(vec);
	vec.push_back(4);
	display(vec);
	vec.push_back(5);
	display(vec);
	vec.push_back(6);
	display(vec);
	vec.push_back(7);
	display(vec);
	cout << endl;
	print(vec);
	cout << endl;
	//
	return 0;
}

/*allocator 简单实现自定义Vector模版

熟悉: 
模板类 static std::allocator<T> alloc; 需要静态声明
static: allocate(n)、deallocate(p,n)  内存的分配和释放     

static: construct(p,args)、destroy(p)  对象的添加与删除

核心: 
reallcote
1.自定义内存不足时，重新分配更大的空间
2.将原空间对象移动move 到新空间(而非copy) | 或者直接使用uninitialized_copy
3.释放原空间资源
*/


/*
    Vector模型
     ______________________________
    |_|_|_|_|_|____________________|
     ↑         ↑                    ↑
   _elems   _first_free            _end
   
           
    T * _elems;      //指向数组中的第一个元素
    T * _first_free; //指向最后一个实际元素之后的那个元素
    T * _end;        //指向数组本身之后的位置
*/
