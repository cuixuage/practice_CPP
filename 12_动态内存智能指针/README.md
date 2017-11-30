** 使用动态内存的常见目的**  

**智能指针也是指针**  
 
+允许多个对象之间的共享底层数据   
当某个对象被拷贝时,我们不必分离原数据\副本数据;或者销毁时必须加以保留 
  
**Shared ptr unique_ptr weak_ptr**  
sp：use_count 引用计数  
up:独享 所有权转移  
wp: lock提升为sp    
 
shared_ptr  unique_ptr往往使用new初始化 因为智能指针默认使用delete释放所关联的对象  
weak_ptr使用shared_ptr初始化  

**优点**  
及时在某函数内部发生的异常未被捕获,导致程序提前结束,智能指针指向的内存块任然能正确释放  
**智能指针陷阱**  
primer P417 