#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


template <typename T, int kSize = 10>       //模板类定义
class Stack
{
public:
	Stack()
	: _top(-1)
	, _arr(new T[kSize]())
	{}

	~Stack();

	bool empty()const;
	bool full() const;
	void push(const T & value);
	void pop();
	T top();
private:
	int _top;
	T * _arr;
};

template <typename T, int kSize>    //成员函数类外定义都需要加上template 以及 class <>
Stack<T, kSize>::~Stack()
{
	delete [] _arr;
}

template <typename T, int kSize>
bool Stack<T, kSize>::empty() const
{
	return _top == -1;
}

template <typename T, int kSize>
bool Stack<T, kSize>::full() const
{
	return _top == kSize - 1;
}

template <typename T, int kSize>
void Stack<T, kSize>::push(const T & value)
{
	if(!full())
	{
		_arr[++_top] = value;
	}
	else
		cout << "栈已满!" << endl;
}

template <typename T, int kSize>
void Stack<T, kSize>::pop()
{
	if(!empty())
	{
		-- _top;
	}
	else
	{
		cout << "栈已空!" << endl;
	}
}

template <typename T, int kSize>
T Stack<T, kSize>::top()
{
	return _arr[_top];
}

class X 
{
public:
						 //此无参的构造函数不加上的话,在template  _arr(new T[kSize]()中出错
	X()                  //error: no matching function for call to ‘X::X()’  , _arr(new T[kSize]())
	: _ix(0)
	{}                 	  //提供无参(参数有默认初始值)的构造函数,以免template初始化error
	
	X(int ix)
	: _ix(ix)
	{}

	friend std::ostream & operator<<(std::ostream & os, const X & rhs);   //ostream必然不会是const
private:
	int _ix;
};
std::ostream & operator<<(std::ostream & os, const X & rhs)
{
	os << rhs._ix;
	return os;
}

int test0(void)
{
	//vector<int> vec;
	Stack<int> stack;
	cout << "此时栈是否为空?" << stack.empty() << endl;
	stack.push(1);
	cout << "此时栈是否为空?" << stack.empty() << endl;
	
	for(int idx = 2; idx != 12; ++idx)
	{
		stack.push(idx);
	}
	cout << "此时栈是否已满?" << stack.full() << endl;

	while(!stack.empty())
	{
		cout << stack.top() << " ";
		stack.pop();
	}
	cout << "此时栈是否为空?" << stack.empty() << endl;

	return 0;
}

int test1(void)
{
	Stack<string> stack;
	cout << "此时栈是否为空?" << stack.empty() << endl;
	stack.push("AAAAAA");
	cout << "此时栈是否为空?" << stack.empty() << endl;
	
	for(int idx = 1; idx != 11; ++idx)
	{
		string elem(6, 'A' + idx);
		stack.push(elem);
	}

	cout << "此时栈是否已满?" << stack.full() << endl;

	while(!stack.empty())
	{
		cout << stack.top() << endl; 
		stack.pop();
	}
	cout << "此时栈是否为空?" << stack.empty() << endl;

	return 0;
}

int main(void)
{
	//test0();
	//test1();
	
	Stack<X> stack;
	cout << "此时栈是否为空?" << stack.empty() << endl;
	stack.push(X(1));
	cout << "此时栈是否为空?" << stack.empty() << endl;
	
	for(int idx = 2; idx != 12; ++idx)
	{
		stack.push(X(idx));
	}

	cout << "此时栈是否已满?" << stack.full() << endl;

	while(!stack.empty())
	{
		cout << stack.top() << endl;     //重载 class X的输出运算符
		stack.pop();
	}
	cout << "此时栈是否为空?" << stack.empty() << endl;
	

	return 0;
}





