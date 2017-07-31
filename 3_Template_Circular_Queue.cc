#include <iostream>
using std::cout;
using std::endl;
//#define MaxSize 10

template <typename T, int MaxSize = 10>
class queue{
private:
	T * _member;
	unsigned int _front;
	unsigned int _rear;
public:
	queue();
	~queue();
	void push (const T &);
	void pop();
	T & front();
	T & back();
	bool empty() const;
	bool full() const;
};

template <typename T , int MaxSize>   //成员函数类外定义都需要加上template 以及 class <>
queue<T,MaxSize>::queue()
:_front(0)
,_rear(0)
,_member(new T[MaxSize]){}

template <typename T , int MaxSize>
queue<T,MaxSize>::~queue(){
		delete [] _member;
}

template <typename T , int MaxSize>
void queue<T,MaxSize>::push(const T & value){
	if((_rear+1)%MaxSize == _front) cout<<"队列已满"<<endl;
	else{
		_member[_rear]=value;
		_rear = (_rear+1)%MaxSize;
	}
}

template <typename T , int MaxSize>
void queue<T,MaxSize>::pop(){
	if(_rear == _front)  cout<<"队列为空"<<endl;
	else _front = (_front+1)%MaxSize;
}

template <typename T , int MaxSize>
T & queue<T,MaxSize>::front(){
	if(_rear != _front) return _member[_front];
}

template <typename T , int MaxSize>
T & queue<T,MaxSize>::back(){
	 //避免元素不断pop,push后，rear==0时,rear-1成为负数
	if(_rear != _front) return _member[(_rear-1+MaxSize)%MaxSize];
}

template <typename T , int MaxSize>
bool queue<T,MaxSize>::empty() const{
	return _rear == _front?true:false;
}

template <typename T , int MaxSize>
bool queue<T,MaxSize>::full() const{
	return (_rear+1)%MaxSize == _front;
}

//***********************自定义新类型
class Xvalue{
private:
	int _xnum;
public:
	Xvalue();
	Xvalue(int );
	friend std::ostream & operator<<(std::ostream &, const Xvalue &rhs);
};
//此无参的构造函数不加上的话,在template  _arr(new T[kSize]()中出错
//error: no matching function for call to ‘X::X()’  , _arr(new T[kSize]())
Xvalue::Xvalue(){}

Xvalue::Xvalue(int xnum)
:_xnum(xnum){}

//友元函数 而非成员函数 operator<<()  不能加入Xvalue定义域
std::ostream & operator<<(std::ostream & oss,const Xvalue & rhs){
	oss<< rhs._xnum ;
	return oss;
}


void test0(){
	queue<int> queueInt;
	cout<<"队列是否为空?"<<" "<<queueInt.empty()<<endl;
	queueInt.push(1);
	cout<<"队列是否为空?"<<" "<<queueInt.empty()<<endl;
	for(int idx=2;idx!=11;++idx){
		queueInt.push(idx);
	}
	
	cout << "此时队列是否已满?" << queueInt.full() << endl;
	while(!queueInt.empty()){
		cout << queueInt.front() << " ";
		queueInt.pop();
	}
	cout << "此时队列是否为空?" << queueInt.empty() << endl;
	return ;
}

void test1(){
	queue<Xvalue> queueX;
	cout<<"队列是否为空?"<<" "<<queueX.empty()<<endl;
	queueX.push(Xvalue(1));
	cout<<"队列是否为空?"<<" "<<queueX.empty()<<endl;
	for(int idx=2;idx!=11;++idx){
		queueX.push(Xvalue(idx));
	}
	
	cout << "此时队列是否已满?" << queueX.full() << endl;
	while(!queueX.empty()){
		cout << queueX.front() << " ";
		queueX.pop();
	}
	cout << "此时队列是否为空?" << queueX.empty() << endl;
	return ;
}

int main(int argc,char** argv){
	//test0();
	test1();
	
	return 0;
}

