
//allocator 简单实现自定义Vector模版
//熟悉 static: allocate、deallocate    故模板类allocator对象需要静态声明
//     construct、destroy(c++17废弃)
//后期: 学习真正的 内部实现 Alloc模板类  二级空间分配器


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
	const T &operator[] (int idx) const;
	int size() const{
		return _firstFree - _elems;
	}
	int capacity() const{
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
			_alloc.destroy(--_firstFree);	
		_alloc.deallocate(_elems,capacity());
	}
	cout<< "~Vector() ok"<<endl;
}

template <typename T>
void Vector<T>::push_back(const T & value){
	if( size() == capacity() )
		reallocate();
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

template <typename T>
void Vector<T>::reallocate(){
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
	return 0;
}

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


/*******************************************************allocator stl源码
STL空间分配接口层 —— 模板类allocator —— 定义

	1. 注:_Tp* allocate(size_type __n)     void deallocate(pointer __p, size_type __n) 是实现层alloc的静态成员函数
		故模板类allocator对象需要静态声明
		
	2. typedef alloc _Alloc;   alloc类是空间分配的实现


template <class _Tp>
class allocator {
  typedef alloc _Alloc;          // The underlying allocator.
public:
  typedef size_t     size_type;
  typedef ptrdiff_t  difference_type;
  typedef _Tp*       pointer;
  typedef const _Tp* const_pointer;
  typedef _Tp&       reference;
  typedef const _Tp& const_reference;
  typedef _Tp        value_type;

  template <class _Tp1> struct rebind {
    typedef allocator<_Tp1> other;
  };

  allocator() __STL_NOTHROW {}
  allocator(const allocator&) __STL_NOTHROW {}
  template <class _Tp1> allocator(const allocator<_Tp1>&) __STL_NOTHROW {}
  ~allocator() __STL_NOTHROW {}

  pointer address(reference __x) const { return &__x; }
  const_pointer address(const_reference __x) const { return &__x; }

  // __n is permitted to be 0.  The C++ standard says nothing about what
  // the return value is when __n == 0.
  _Tp* allocate(size_type __n, const void* = 0) {
    return __n != 0 ? static_cast<_Tp*>(_Alloc::allocate(__n * sizeof(_Tp))) 
                    : 0;
  }

  // __p is not permitted to be a null pointer.
  void deallocate(pointer __p, size_type __n)
    { _Alloc::deallocate(__p, __n * sizeof(_Tp)); }

  size_type max_size() const __STL_NOTHROW 
    { return size_t(-1) / sizeof(_Tp); }

  void construct(pointer __p, const _Tp& __val) { new(__p) _Tp(__val); }
  void destroy(pointer __p) { __p->~_Tp(); }
};
*****************************************************/