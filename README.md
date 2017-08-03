# Practice_CPP
**1.String.cc**  
自定义string类 掌握无参数、带参数、对象浅拷贝、对象深拷贝等构造函数以及=重载函数的定义格式（7题深入）     
**2.stack.cc**    
自定义stack类 使用数组元素模仿当中数据成员 若栈溢出则结束当前进程    
**3.circular_queue.cc**    
自定义队列类 循环队列避免单向队列的假溢出  
**4.Singleton_MultiVersion.cc**   
三个版本的单例模式,pthread_once + atexit保证多线程情景下懒汉单例模式安全,以及单实例的自动释放    
**5.Word_frequency.cc**   
统计the holy bible中单词词频,去除标点ispunct、转为小写islower tolower、去除数字isdigit等宏定义  
版本二: 支持单词查询  
**6.Log4cpp.cc**  
日志C++库 log4cpp的layout fileappender category的使用 -llog4cpp -lpthread  
**7.StringOperator.cc**   
实现Stinrg 类中 构造函数、运算符= += == != > < >= <=、输入输出流istream ostream的重载   
**8.String_COW_WriteAndRead.cc**   
String 类Copy_On_Write 技术实现： 申请堆空间时而外申请sizeof(cahr)大小空间用于保存引用计数值    
Proxy 模式区别operator[]运算符的write(引用计数自减) , read情况  ————Effective C++    

