//循环队列避免单向队列的假溢出
// front指向队首元素，rear指向队尾元素的下一个元素
//少用一个元素空间，约定  队空时： front==rear  队满时： (rear+1)%maxsize==front

#include <iostream>       
using std::cout;
using std::endl;
#define MaxSize 10

class queue{
private:
	unsigned int size;
	int* member;
	unsigned int _front;
	unsigned int rear;
public:
	queue();
	~queue();
	void push(int);
    void pop();
    int front();
    int back();
    bool empty();
	bool full();
	
	int getrear();
	int get_front();
};

queue::queue()
:size(0)
,member(new int[MaxSize])
,_front(0)
,rear(0){}

queue::~queue(){
	delete [] member;
}

void queue::push(int num){
	if((rear+1)%MaxSize == _front) return ;
	else{
		member[rear]=num;
	    rear = (rear+1)%MaxSize;
	}
}

void queue::pop(){
	if(rear==_front) return ;
	else _front = (_front+1)%MaxSize;
}

int queue::front(){
	if(rear!=_front) return member[_front];
}

int queue::back(){
	//if(rear!=_front) return member[rear-1];     //error 考虑元素不断pop,push后，rear==0时,rear-1成为负数
	if(rear!=_front){    //元素不为空
		if(rear==0) return member[MaxSize-1];
		else return member[rear-1];
	}
}

bool queue::empty(){
	return rear==_front?true:false;
}

bool queue::full(){
	return (rear+1)%MaxSize==_front?true:false;
}

int queue::getrear(){
	return rear;
}

int queue::get_front(){
	return _front;
}


int main(int argc,char** argv){
	queue que;
	cout<<"empty?"<<que.empty()<<endl;
	
	que.push(10);
	que.push(11);
	que.push(12);
	que.push(13);
	que.push(14);
	que.push(15);
	que.push(16);
	que.push(17);
	que.push(18);
	cout<<"full?"<<que.full()<<endl;
	cout<<"front="<<que.front()<<endl;
	cout<<"rear="<<que.back()<<endl;
	
    que.pop();
	cout<<"full?"<<que.full()<<endl;
	cout<<"after pop,front="<<que.front()<<endl;
	cout<<"rear="<<que.back()<<"   "<<que.getrear()<<endl;
	
    que.push(19);
	cout<<"front="<<que.front()<<endl;
	cout<<"rear="<<que.back()<<"   "<<que.getrear()<<endl;
    cout<<"full?"<<que.full()<<endl;
	return 0;
}
