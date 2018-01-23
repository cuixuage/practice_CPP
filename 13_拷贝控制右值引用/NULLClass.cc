#include <iostream>
#include<stdlib.h>
using std::cout;
using std::endl;
class testNULL{
public:
    virtual void func();
};
void testNULL::func(){
    cout<<"parents"<<endl;
}
class testNULLChild : public testNULL{
public:
        void func();
};
void testNULLChild::func(){
    cout<<"child"<<endl;
}
//多态性
void display(testNULL* tmp){
    tmp->func();
}
int main(int argc,char** argv){
    cout<<sizeof(testNULL)<<endl;
    cout<<sizeof(testNULLChild)<<endl;
    testNULL* parents = new testNULL();
    testNULLChild* child = new testNULLChild();
    display(child);
    display(parents);
    return 0;
}

/*
1.sizeof(空类) == 1bytes
2.空类可以实例化，实例化编译器默认提供以下函数:
class Empty
{
  public:
    Empty();                            //缺省构造函数
    Empty(const Empty &rhs);            //拷贝构造函数
    ~Empty();                           //析构函数
    Empty& operator=(const Empty &rhs); //赋值运算符
    Empty* operator&();                 //取址运算符
    const Empty* operator&() const;     //取址运算符(const版本)
};

Empty *e = new Empty();    //缺省构造函数
delete e;                  //析构函数
Empty e1;                  //缺省构造函数
Empty e2(e1);              //拷贝构造函数
e2 = e1;                   //赋值运算符
Empty *pe1 = &e1;          //取址运算符(非const)
const Empty *pe2 = &e2;    //取址运算符(const)


*/
