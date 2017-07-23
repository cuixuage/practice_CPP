#include <iostream>       
#include <sys/types.h>
#include <signal.h> 
#include <unistd.h>
using std::cout;
using std::endl;
#define N 10

class stack{
private:
	unsigned int size;
	int* member;
public:
	stack();
	~stack();
	void push(int);
	void pop();
	int top();         //栈顶是数组中最后一个
	bool empty();
	bool full();
};

stack::stack()
:size(0)
,member(new int[N]){}

stack::~stack(){
	delete [] member;
}

void stack::push(int num){
	if(size>=N) kill(getpid(),SIGKILL);   //栈溢出,结束进程
	else{
		member[size] = num;
		size++;
	}
}

void stack::pop(){
	if(size==0) kill(getpid(),SIGKILL);   //栈溢出,结束进程
	else size--;
}

int stack::top(){
	if(size>=1 && size<=N) return member[size-1];
}

bool stack::empty(){
	return size==0?true:false;
}

bool stack::full(){
	return size==N?true:false;
}
	
int main(int argc,char** argv){
	stack stk;
	cout<<"empty?"<<stk.empty()<<endl;
	
	stk.push(10);
	stk.push(12);
	stk.push(14);
	int top=stk.top();
	cout<<"top: "<<top<<endl;
	stk.pop();
	top=stk.top();
	
	cout<<"after pop,top: "<<top<<endl;
	cout<<"full?"<<stk.full()<<endl;
	
	return 0;
}
	
	