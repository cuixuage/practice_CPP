#include <iostream>
using std::cout;
using std::endl;
void const_test(int& a,int& b){	
	//-------常量指针-------
    const int *p1 = &a;			//int const* p1=&a
    a = 300;     //OK,仍然可以通过原来的声明修改值，
    //*p1 = 56;  //Error,*p1是const int的，不可修改，即常量指针不可修改其指向地址
    p1 = &b;     //OK,指针还可以指向别处，因为指针只是个变量，可以随意指向；
	cout<<*p1<<endl;

    //-------指针常量-------//
    int*  const p2 = &a;
    a = 500;     //OK,仍然可以通过原来的声明修改值，
    *p2 = 400;   //OK,指针是常量，指向的地址不可以变化,但是指向的地址所对应的内容可以变化
    //p2 = &b;     //Error,因为p2是const 指针，因此不能改变p2指向的内容
    
    //-------指向常量的常量指针-------//
    const int* const p3 = &a;
    //*p3 = 1;    //Error
    //p3 = &b;    //Error
    a = 5000;    //OK,仍然可以通过原来的声明修改值
}

int  main(){
	int a=5;
	int b=6;
	const_test(a,b);
	cout<<"a:"<<a<<endl;
	return 0;
}