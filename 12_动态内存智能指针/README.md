** 使用动态内存的常见目的**  
1.  
**智能指针也是指针**  
+允许多个对象之间的共享底层数据   
当某个对象被拷贝时,我们不必分离原数据\副本数据;或者销毁时必须加以保留 
  
**区别**  
sp：use_count 引用计数  
up:独享 所有权转移  
wp: lock提升为sp    
 
shared_ptr  unique_ptr 往往使用new初始化 因为智能指针默认使用delete释放所关联的对象  
weak_ptr使用shared_ptr初始化  

**优点**  
及时在某函数内部发生的异常未被捕获,导致程序提前结束,智能指针指向的内存块任然能正确释放  
**智能指针陷阱**  
primer P417 

2.  
**allocator模板类**  
目的: 分离内存分配和初始化工作 可以自定义的初始化  
实例:  
allocator 简单实现自定义Vector模版  
熟悉:  
模板类 static std::allocator<T> alloc; 需要静态声明  
static: allocate(n)、deallocate(p,n)  内存的分配和释放       
static: construct(p,args)、destroy(p)  对象的添加与删除  
核心:  
reallcote   
1.自定义内存不足时，重新分配更大的空间  
2.将原空间对象移动move 到新空间(而非copy) | 或者直接使用uninitialized_copy  
3.释放原空间资源  



